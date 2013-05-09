#include <iostream>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <memory>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <algorithm>

#include <unistd.h>
#include "message_passing.h"


namespace mp {

queue::queue() : return_token_count_ ( 0 ), do_stop_ ( false ) {
    
    
}
void queue::emplace_msg ( typeinfo_wrapper&& typeinfo, std::unique_ptr< msg::base > msg, size_t token, bool return_msg )
{
    std::unique_lock<std::mutex> lock ( central_mtx_ );
    q_.emplace_back ( std::move ( typeinfo ), std::move ( msg ), token, return_msg );

    lock.unlock();
    q_cond_.notify_one();
}
void queue::dispatch ( queue::q_entry_type&& ent )
{
    auto it = handler_map_.find ( ent.wrap_ );

    if ( it == handler_map_.end() ) {
        std::cerr << "no handler for type: " << ent.wrap_.name() << "\n";
        return;
    }

    it->second ( std::move ( ent.msg_ ) );


}
void queue::dispatch_ret ( queue::q_entry_type&& ent, queue::return_entry_type ret_ent, size_t token )
{
    auto it = handler_ret_map_.find ( ent.wrap_ );

    if ( it == handler_ret_map_.end() ) {
        std::cerr << "no handler_ret for type: " << ent.wrap_.name() << "\n";
        return;
    }

    std::unique_ptr<msg::base> ret_msg = it->second ( std::move ( ent.msg_ ) );
    ret_ent.q_->emplace_msg ( std::move ( ret_ent.typeinfo_ ), std::move ( ret_msg ), token, true );

}
bool queue::dispatch_pop()
{


    std::unique_lock<std::mutex> lock ( central_mtx_ );

//         if( q_.empty() ) {
//             return false;
//         }

    while ( q_.empty() && !do_stop_ ) {
        q_cond_.wait ( lock );
    }

    if ( do_stop_ ) {
        return false;
    }

    q_entry_type ent {std::move ( q_.front() ) };
    q_.pop_front();



    if ( ent.return_token_ == TOKEN_NONE ) {

        lock.unlock();
        dispatch ( std::move ( ent ) );
    } else {

        if ( !ent.return_msg_ ) {
            auto it = return_map_.find ( ent.return_token_ );

            if ( it == return_map_.end() ) {
                std::cerr << "no target queue for return token: " << ent.return_token_ << "\n";
                return true;
            }

            auto ret_entry = it->second;
            return_map_.erase ( it );

            lock.unlock();

            dispatch_ret ( std::move ( ent ), ret_entry, ent.return_token_ );
        } else {



            auto it = token_handler_map_.find ( ent.return_token_ );

            if ( it == token_handler_map_.end() ) {
                std::cerr << "no token return handler: " << ent.return_token_ << "\n";
                return true;
            }

            auto func = it->second;
            token_handler_map_.erase ( it );

            lock.unlock();

            func ( std::move ( ent.msg_ ) );

        }
    }



    return true;

}
void queue::stop()
{
    std::unique_lock<std::mutex> lock ( central_mtx_ );
    do_stop_ = true;

    lock.unlock();
    q_cond_.notify_all();
}
bool queue::is_stopped() const
{
    std::lock_guard<std::mutex> lock ( central_mtx_ );
    return do_stop_;

}
void queue::add_default_stop_handler()
{
    add_handlerx<msg::stop> ( [this] ( std::unique_ptr<msg::stop> m ) {
        stop();
    } );
}
} // namespace mp





