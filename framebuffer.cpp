#if 1
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
        
     /*   XImage *xi = XShmCreateImage(display_, DefaultVisual( display_, 0 ), DefaultDepthOfScreen(screen),
                          ZPixmap, NULL, &shminfo,
                          width_, height_);
     */   
     
        
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


int main( int argc, char *argv[] ) {
    
  //  shm_obj t( 1024 * 1024 );
    
    framebuffer fb;
    
    fb.set_foreground(0xFFFFFFFF);
    fb.draw_point( 100, 100 );
    fb.flush();
    
    
    
    
    
    
    while( true ) {
        fb.draw_point( rand() % fb.width(), rand() % fb.height() );
        fb.flush();
        getchar();
    }
    
    
    
}

#else
int main( int argc, char *argv[] ) {
}
#endif