#include "mp2.h"


d3d::ortho::mp2::queue::queue() : b_stop_(false), next_return_token_(1) {
}

d3d::ortho::mp2::queue::~queue() {
    stop_handler_guard_ = callback_guard();
    if( !handler_map_.empty() ) {
        std::cout << "WARNING: queue destroyed with callbacks still registered: " << handler_map_.size() << "\n";
    }
}

void d3d::ortho::mp2::queue::stop() {
    std::unique_lock<std::mutex> lock(mtx_);
    b_stop_ = true;
    cond_var_.notify_all();
}

bool d3d::ortho::mp2::queue::is_stopped() {
    std::unique_lock<std::mutex> lock(mtx_);
    return b_stop_;
}

bool d3d::ortho::mp2::queue::dispatch_pop() {
    std::unique_lock<std::mutex> lock(mtx_);

    while( q_.empty() && !b_stop_ ) {
        cond_var_.wait(lock);
    }

    if( b_stop_ ) {
        return false;
    }
    const auto &ti = std::get<0>(q_.front());
    //            abstract_msg &msg = *q.front().second;


    std::unique_ptr<abstract_msg> msg = std::move(std::get<1>(q_.front()));
    auto *target_q = std::get<2>(q_.front());
    auto token = std::get<3>(q_.front());
    std::unique_ptr<abstract_dispatcher> delete_dispatcher;
    abstract_dispatcher *dispatcher = nullptr;

    if( token != 0 && target_q == 0 ) {
        auto it = token_handler_map_.find(std::make_pair(ti, token));
        assert( it != token_handler_map_.end() );
        dispatcher = it->second.get();

        // erase dispatcher from token handler map
        // and delete the dispatcher after the call has returned (via the unique ptr)
        delete_dispatcher = std::move(it->second);
        token_handler_map_.erase(it);

    } else {
        auto it = handler_map_.find(ti);
        assert( it != handler_map_.end() );
        dispatcher = it->second.get();
    }

    //it->second(*msg);
    q_.pop_front();
    lock.unlock();

    dispatcher->dispatch(std::move(msg), target_q, token);

    return true;
}

void d3d::ortho::mp2::queue::unregister_callback(handler_map_type::iterator iter) {
    handler_map_.erase(iter);
}


d3d::ortho::mp2::queue::callback_guard::callback_guard(d3d::ortho::mp2::queue::callback_guard &&other)  {
    unregister();

    q_ = other.q_;
    iter_ = other.iter_;
    other.q_ = nullptr;
}

d3d::ortho::mp2::queue::callback_guard &d3d::ortho::mp2::queue::callback_guard::operator=(d3d::ortho::mp2::queue::callback_guard &&other) {
    unregister();

    q_ = other.q_;
    iter_ = other.iter_;
    other.q_ = nullptr;

    return *this;
}

d3d::ortho::mp2::queue::callback_guard::~callback_guard() {
    unregister();
}

void d3d::ortho::mp2::queue::callback_guard::unregister() {
    if(q_ != nullptr) {
        q_->unregister_callback(iter_);
        q_ = nullptr;
    }
}
