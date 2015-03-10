
#include "mp3.h"

#include <cassert>


using namespace d3d::mp3;

dispatcher::dispatcher() : next_token_(1)
{}

void dispatcher::invoke(std::type_index ti, void *msg_ptr, std::unique_lock<std::mutex> &&lock)
{
    auto it = handler_map.find(ti);
    assert(it != handler_map.end());
    lock.unlock();

    it->second->handle(msg_ptr);
}

std::pair<std::type_index, void *> dispatcher::invoke_ret(std::type_index ti, void *msg_ptr, std::unique_lock<std::mutex> &&lock)
{
    auto it = handler_map_ret.find(ti);
    assert(it != handler_map_ret.end());
    lock.unlock();

    return it->second->handle(msg_ptr);
}

void dispatcher::invoke_token(size_t token, void *msg_ptr, std::unique_lock<std::mutex> &&lock)
{
    auto it = handler_map_ret_token.find(token);
    assert(it != handler_map_ret_token.end());

    std::unique_ptr<abstract_handler_token> handler = std::move(it->second);
    handler_map_ret_token.erase(it);
    lock.unlock();

    handler->handle(token, msg_ptr);
}


bool queue::dispatch_pop()
{
    std::unique_lock<std::mutex> lock(mtx_);

    while( queue_.empty() && !b_stop_ )
    {
        cond_var_.wait(lock);
    }

    if( b_stop_ )
    {
        return false;
    }

    std::type_index ti = std::get<0>(queue_.front());
    void *msg_ptr = std::get<1>(queue_.front());
    size_t token = std::get<2>(queue_.front());
    queue *target_queue = std::get<3>(queue_.front());
    queue_.pop_front();


    if( token == 0 && target_queue == nullptr )
    {
        // normal call
        dispatcher::invoke(ti, msg_ptr, std::move(lock));
    }
    else if( token != 0 && target_queue != nullptr )
    {
        // call with return message (first half of roundtrip)
        const auto &p = dispatcher::invoke_ret(ti, msg_ptr, std::move(lock) );
        target_queue->call_token(std::get<0>(p), std::get<1>(p), token);
    }
    else if( token != 0 && target_queue == nullptr )
    {
        // return message (second half of roundtrip)
        dispatcher::invoke_token(token, msg_ptr, std::move(lock));
    }


    return true;
}
