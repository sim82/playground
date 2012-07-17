#include <atomic>
#include <iostream>
#include <vector>

class test {
public:
    
    test() : v1_(1024 * 1024), v2_(1024 * 1024) {
        
        p1_ = v1_.data();
        p2_ = v2_.data();
        
    }
    
private:
    
    
    
    void work( int rank ) {
        
        while( true ) {
            float *p1 = p1_.load();
            float *p2 = p2_.load();
            
            
            if( rank == 0 ) {
                p1 = p2_.exchange(p1);
                p1_.store(p1);
            }
            
            
            
            p2[rank] = p1[rank];
            
            if( p1 == p2 ) { 
                std::cerr << "meeeeeep" << std::endl;
                
            }
               
            
        }
    }
    std::vector<float> v1_;
    std::vector<float> v2_;
    
    std::atomic<float *>p1_;
    std::atomic<float *>p2_;
    
};

int main() {
    std::atomic<float *> aptr;
    
//     std::cout << "is lock free: " << aptr.is_lock_free() << "\n";
}