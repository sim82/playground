#include <functional>
#include <iostream>

class scope_rollback {
public:
    scope_rollback( std::function<void()> f ) : f_(f), commit_(false) {}
    
    ~scope_rollback() {
        if( !commit_ ) {
            f_();
        }
    }
    
    void commit() {
        commit_ = true;
    }
    
    scope_rollback() = delete;
    scope_rollback( const scope_rollback & ) = delete;
    scope_rollback( scope_rollback && ) = delete;
    
    scope_rollback &operator=(const scope_rollback & ) = delete;
    scope_rollback &operator=(scope_rollback && ) = delete;
    
private:
    std::function<void()> f_;
    bool commit_;
    
};


int main() {
    
    std::cout << "bla\n";
    scope_rollback r([]() {
        std::cout << "rollback bla\n";
    });
    
    std::cout << "do something\n";
    r.commit();
    
    
    
}