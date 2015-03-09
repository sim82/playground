#include <iostream>
#include <vector>
#include <algorithm>

template<typename K, typename V>
class binary_heap {



public:

    typedef std::pair<K,V> kv_type;

    inline size_t left( size_t i ) {
        return 2 * i + 1;
    }

    inline size_t right( size_t i ) {
        return 2 * i + 2;
    }

    inline size_t parent( size_t i ) {
        return (i - 1) / 2;
    }

    void heapify( size_t a ) {
        size_t i = a;
        const size_t size = h_.size();
        while(true) {
            size_t min = i;

            const size_t l = left(i);
            if( l < size && h_[l].first < h_[min].first ) {
                min = l;
            }
            const size_t r = right(i);
            if( r < size && h_[r].first < h_[min].first ) {
                min = r;
            }

            if( min == i ) {
                break;
            }
            std::swap( h_[i], h_[min]);
            i = min;
        }
    }

    void build() {
        if( !h_.empty() ) {
            for( ssize_t i = h_.size() / 2 - 1; i >= 0; --i ) {
                heapify( i );
            }
        }
    }

    void decrease( size_t i, const K &newkey ) {
        h_[i].first = newkey;

        const size_t p = parent(i);
        while( i > 0 && h_[i].first < h_[parent(i)].first) {
            std::swap( h_[i], h_[p]);
            i = p;
        }
    }
    void push( const K &k, const V &v ) {
        h_.emplace_back(k, v);
        decrease(h_.size() - 1, k );
    }

    void remove( size_t i ) {
        size_t last_idx = h_.size() - 1;
        std::swap( h_[i], h_[last_idx] );
        h_.pop_back();

        if( i != last_idx ) {
            if( i == 0 || h_[i].first < h_[parent(i)].first ) {
                heapify(i);
            } else {
                decrease( i, h_[i].first );
            }
        }
    }

    const kv_type& top() {
        return h_.front();
    }

    void pop() {
        remove( 0 );
    }


    std::vector<kv_type> &h() {
        return h_;
    }

private:
    std::vector<kv_type> h_;
};

int main() {
    srand(1234);
    binary_heap<int,int> heap;
    for( size_t i = 0; i < 20; ++ i ) {
        heap.h().emplace_back( rand() % 100, i );
    }

    heap.build();

    for( auto it = heap.h().begin(); it != heap.h().end(); ++it ) {
        std::cout << it->first << "\n";
    }

    heap.decrease(4, 5);

    for( auto it = heap.h().begin(); it != heap.h().end(); ++it ) {
        std::cout << it->first << "\n";
    }

    while( !heap.h().empty() ) {
        std::cout << heap.top().first << "\n";
        heap.pop();
    }
}
