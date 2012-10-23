#include <cassert>

#include <stdexcept>
#include <iostream>
#include <cstdint>

#include <sys/shm.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XShm.h>
// #include <X11/extensions/xf86dga.h>
// #include <X11/extensions/xf86vmode.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <boost/uuid/uuid_io.hpp>
#include "entity.h"
#include "game1_entity.h"
#include "cycle.h"
#include "time.h"


double ivy_mike::perf_timer::my_getticks() {
#if defined(WIN32) && !defined(_M_X64)
        return double(getticks().QuadPart);
#else
        return double(getticks());
#endif
}


class shm_obj {
    
public:

    shm_obj( size_t size ) : shmid_(-1), shmptr_(0) {
        shmid_ = shmget (IPC_PRIVATE, size, IPC_CREAT|0777);
        
    }
    
    ~shm_obj() {
        if( shmid_ != -1 ) {
            assert( shmptr_ != 0 );
            shmdt( shmptr_ );
            
            shmctl( shmid_, IPC_RMID, 0 );
        }
    }
    
    const int shmid() const {
        return shmid_;
    }
private:
    int shmid_;
    void *shmptr_;
};

class framebuffer {
    
public:
    framebuffer( uint32_t width = 800, uint32_t height = 600 ) : width_(width), height_(height) {
        
        
        {
            // select display and screen
            const char *dpyName = ":0";
            display_ = XOpenDisplay( dpyName );
            scrnum_ = DefaultScreen( display_ );
            if( display_ == 0 ) {
                throw std::runtime_error( "X11 display == 0\n" );
            }
        
        }
        
        
        {
            // create window
            
            Window root;
            root = RootWindow( display_, scrnum_ );
            
            XSetWindowAttributes attr;                   
            attr.background_pixel = 0;
            attr.border_pixel = 0;
            attr.colormap = XCreateColormap( display_, root, DefaultVisual( display_, 0 ), AllocNone );
            attr.event_mask =  StructureNotifyMask | ExposureMask | KeyPressMask | FocusChangeMask;
            unsigned long mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;
            
            window_ = XCreateWindow( display_, root, 0, 0, width, height,
                                      0, DefaultDepth(display_, 0), InputOutput, DefaultVisual(display_, 0), mask, &attr );
            
            if( window_ == 0 )
            {
                
                throw std::runtime_error( "XCreateWindow failed\n" );
            }
        
        }
        
        
        {
            // additional window setup
            XSizeHints sizehints;
            sizehints.width = width_;
            sizehints.height = height_;
            sizehints.flags = USSize;
            XSetNormalHints( display_, window_, &sizehints );
            
            const char *name = "Human Interface";
            // is XSetNormalHints above just plain stupid?
            XSetStandardProperties( display_, window_, name, name, None, (char**)0, 0, &sizehints );   
        }
        
        
        XMapWindow( display_, window_ );
        
        // wait for map notify
        while(true) {
            XEvent e;
            XNextEvent(display_, &e);
            std::cout << "event: " << e.type << "\n";
            if (e.type == MapNotify) {
                break;
            }
        }
        
        
        // done
        
        gc_ = XCreateGC( display_, window_, 0, 0 );
    
        
//         shminfo.
#if 0    
        XImage *xi = XShmCreateImage(display_, DefaultVisual( display_, 0 ), DefaultDepthOfScreen(screen),
                          ZPixmap, NULL, &shminfo,
                          width_, height_);
#endif   
     
        
    }
    
    
    void set_foreground( uint32_t fg ) {
        XSetForeground( display_, gc_, fg );
    }

    void flush() {
        XFlush(display_);
    }
    
    void draw_point( int x, int y ) {
        XDrawPoint( display_, window_, gc_, x, y );
    }
    
    
    uint32_t width() const {
        return width_;
    }
    
    uint32_t height() const {
        return height_;
    }
    
private:
    Window  window_;
    Display *display_;
    GC gc_;
    
    int     scrnum_; // is valid if theDisplay != 0
    
    
    uint32_t width_;
    uint32_t height_;
    
    XShmSegmentInfo shminfo;
            
};


int main() {
    entity_store es;
    
    entity_ptr::global_store = &es;
    
    
    std::vector<entity_ptr> thinkers;
    std::vector<entity_ptr> points;
    
    framebuffer fb;
    
    fb.set_foreground(0xFFFFFFFF);
    fb.draw_point( 100, 100 );
    fb.flush();
    
    
    auto player = es.create();
    {
        
        player->make_member<member_2d_point>( 100, 100 );
        player->make_member<member_thinker,member_player_character>();
        
        thinkers.emplace_back( player->id() );
        points.emplace_back( player->id() );
        global_prey.emplace_back( player->id() );
    }
    
    for( size_t i = 0; i < 10000; ++i ) 
    {
        auto hunter = es.create();
        hunter->make_member<member_2d_point>( rand() % fb.width(), rand() % fb.height() );
        hunter->make_member<member_thinker,member_hunter>();
        
        thinkers.emplace_back( hunter->id() );
        points.emplace_back( hunter->id() );
    }
    
    
    ivy_mike::perf_timer t1;
    
    
    for( size_t frame = 0; frame < 10000; ++frame ) {
        double dtime = 0.1;
//         std::cout << "=========================\n";
        for( auto & ent : thinkers ) {
             ent.lock()->member<member_thinker>().think( dtime );
//              std::cout << "think: " << ent.lock()->id() << "\n";
             
        }
        
        bool do_draw = false;
        if( frame % 1000 == 0 ) {
            std::cout << "frame: " << frame << "\n";
            player->member<member_2d_point>().set( rand() % fb.width(), rand() % fb.height() );
            do_draw = true;
        }
        
        for( auto & ent : points ) {
             auto & point = ent.lock()->member<member_2d_point>();
             int x = point.x();
             int y = point.y();
             
             if( do_draw ) {
                 fb.draw_point( x, y );
             }
             
             
            
        }
        if( do_draw ) {
            fb.flush();
        }
//         getchar();
        
    }
    t1.add_int();
    t1.print();
    
}
