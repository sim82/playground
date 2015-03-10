#include <cassert>
#include <memory>
#include <iostream>

class coroutine {
public:
    virtual ~coroutine() {}

    virtual bool step() = 0;
};


class nested_coroutine : public coroutine {
public:
    void start_nested( std::unique_ptr<nested_coroutine> nested ) {
        assert( !nested_ );
        nested_ = std::move(nested);
        nested_done_ = false;
    }
    bool step() override {
        if( nested_ && !nested_done_ ) {
            auto res = nested_->step();

            nested_done_ = !res;

            return true;
        }

        return step_impl();
    }
    template<typename nested_coroutine_type>
    std::unique_ptr<nested_coroutine_type> nested_done() {
        if( !nested_ || !nested_done_ ) {
            return std::unique_ptr<nested_coroutine_type>();
        }
        auto *rp = dynamic_cast<nested_coroutine_type*>(nested_.get());

        assert( rp != nullptr );
        nested_.release();

        return std::unique_ptr<nested_coroutine_type>(rp);
    }

    virtual bool step_impl() = 0;
private:
    std::unique_ptr<nested_coroutine> nested_;
    bool nested_done_;
};

class coroutine2 : public nested_coroutine {
public:
    coroutine2() : step_() {}

    bool step_impl() override {
        std::cout << "coroutine2 step " << step_ << "\n";
        if( step_ < 4 ) {
            ++step_;
            return true;
        } else {
            return false;
        }

        return true;
    }

private:
    int step_;
};

class coroutine1 : public nested_coroutine {
public:
    coroutine1() : step_(0), is_done_(false) {}

    bool step_impl() override {
        std::cout << "coroutine1 step " << step_ << "\n";

        switch(step_) {
        case 0:
            step_ = 1;
            i_step1_ = 0;
            break;

        case 1:
        {
            if( i_step1_ < 5 ) {
                auto c2 = nested_done<coroutine2>();
                if( c2 ) {
                    std::cout << "nested done\n";
                    ++i_step1_;
                    break;
                } else {
                    std::cout << "start nested " << i_step1_ << "\n";
                    start_nested(std::make_unique<coroutine2>());
                    break;
                }
            }
            step_ = 2;
            break;

        }
        case 2:
            is_done_ = true;
            break;
        }

        return !is_done_;
    }

private:

    int step_;
    bool is_done_;

    int i_step1_;
};

int main() {
    coroutine1 c1;

    while( c1.step() ) {

    }

}
