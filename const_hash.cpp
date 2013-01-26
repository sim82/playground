#include <cstdint>
#include <climits>
#include <stdexcept>

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <iostream>
#include <memory>
#include <sstream>
#include <deque>
#include <limits>
#include <array>
#include <iterator>
#include <cassert>

template<typename K>
int hash_value( const K &k ) {
    return k.hash();
}

template<>
int hash_value( const std::string &s ) {
    int h = 0;
    
    for( size_t i = 0; i < s.size(); ++i ) {
        h *= 13;
        h += s[i];
    }
    
    return h;
}


template<typename K, typename V, size_t s, size_t max_size>
class hashtable {
public:
    hashtable() {
        std::fill( table_, table_ + s, (link*)0 );
    }
     
    
    void insert( const K &k, const V &v ) {
        const int slot = get_slot(k);
    
        //link *l = new link( k, v );
        link *l = alloc_.alloc(k, v);
        l->next_ = table_[slot];
        table_[slot] = l;
    }
    
    const V * find( const K &k ) {
        const int slot = get_slot(k);
        
        link *l = table_[slot];
        while( l != 0 ) {
            if( l->key_ == k ) {
                return &l->value_;
            }
            
            l = l->next_;
            
        }
        return &l->value_;;
    }
    
    void remove( const K &k ) {
        const int slot = get_slot(k);
        
        link *l = table_[slot];
        link *l_prev = 0;
        while( l != 0 ) {
            
            
            if( l->key_ == k ) {
                if( l_prev != 0 ) {
                    l_prev->next_ = l->next_;
                } else {
                    table_[slot] = l->next_;
                }
                
                l_prev = l;
                link *l_del = l;
                l = l->next_;
                
                //delete l_del;
                alloc_.dealloc(l_del);
            } else {
                l_prev = l;
                l = l->next_;
            }
        }
        
    }
    
    void print_stat() {
        
        size_t len_min = std::numeric_limits<size_t>::max();
        size_t len_max = 0;
        size_t len_sum = 0;
        
        for( size_t i = 0; i < s; ++i ) {
            size_t chain_len = 0;
            
            
            
            for( link *l = table_[i]; l != 0; l = l->next_, ++chain_len ) {
                
            }
            
            
            std::cout << "slot: " << i << " " << chain_len << "\n";
            len_min = std::min( len_min, chain_len );
            len_max = std::max( len_max, chain_len );
            len_sum += chain_len;
        }
        
        std::cout << "min/max/avg: " << len_min << " " << len_max << " " << len_sum / float(s) << "\n";
    }
    
private:
    size_t get_slot( const K &k ) {
        return hash_value( k ) % s;
    }
    
    struct link {
        link() {}
        
        link( const K &k, const V &v ) : key_(k), value_(v) {
        }
        
        K key_;
        V value_;
        link *next_;
    };
    

    class link_allocator {
    public:
        //link_allocator() : free_list_(0) {}
        
        link_allocator() : heap_next_(0), free_list_(0) {}
        
        link *alloc( const K &k, const V &v ) {
            link *ret = 0;
            
            if( free_list_ != 0 ) {
                free_list_->key_ = k;
                free_list_->value_ = v;
                ret = free_list_;
                free_list_ = free_list_->next_;
            } else {
                //links_.push_back( link(k, v) );
                if( heap_next_ >= max_size ) {
                    throw std::runtime_error( "out of heap" );
                }
                
                ret = &heap_[heap_next_];
                ret->key_ = k;
                ret->value_ = v;
                ++heap_next_;
                
                //ret = &links_.back();
            }
            
            return ret;
        }
        
        void dealloc( link *l ) {
            
            l->next_ = free_list_;
            free_list_ = l;
        }
        
        
        //std::deque<link> links_;
        
        link heap_[max_size];
        size_t heap_next_;
        
        link *free_list_;
    };
    
    link *table_[s];
    link_allocator alloc_;
    
    
};


template<typename T>
T partition( T left, T right, T pivot ) {
    std::swap( *pivot, *right );
    
    T insert = left;
    T cur = left;
    while( cur < right ) {
        if( *cur < *right ) {
            std::swap( *cur, *insert );
            ++insert;
        }
        
        ++cur;
    }
    
    std::swap( *right, *insert );
    
    return insert;
    
}

template<typename T>
void quicksort( T start, T end ) {
    assert( start <= end );
    
    if( start == end || start == end - 1 ) {
        return;
    }
    
    size_t len = std::distance( start, end );
    size_t p_ind = len / 2;

    T pivot = start + p_ind;
    
    T bound = partition( start, end - 1, pivot );
    
    quicksort( start, bound );
    quicksort( bound + 1, end );
    
}


int partition_simple( int *arr, int left, int right, int pivot ) {
    assert( left < right );
    
    std::swap( arr[pivot], arr[right] );
    
    int insert = left;
    int cur = left;
    
    while( cur != right ) {
        if( arr[cur] < arr[right] ) {
            std::swap( arr[cur], arr[insert] );
            ++insert;
        }
        
        ++cur;
    }

    std::swap( arr[insert], arr[right] );
    
    return insert;
}


void quicksort_simple( int *arr, int left, int right ) {
    if( right - left >= 2 ) {
        
        int mid = (left + right) / 2;
        // partition
        int bound = partition_simple( arr, left, right, mid );
        
        quicksort_simple(arr, left, bound - 1 );
        quicksort_simple(arr, bound + 1, right );
    }
}

int main() {
    {
        std::array<int,10> x = {{2,5,6,3,4,2,6,5,3,2}};
//         std::array<int,2> x = {{5,2}};
       quicksort( x.begin(), x.end() );
//         quicksort_simple(x.data(), 0, x.size() - 1 );
        
        std::copy( x.begin(), x.end(), std::ostream_iterator<int>(std::cout, "\n" ));
        return 0;
    }
    
    hashtable<std::string,int,256,1000> ht;
    
    for( size_t i = 0; i < 1000; ++i ) {
        std::stringstream ss;
        
        ss << "key" << i;
        
        ht.insert( ss.str(), i );
    }
    
    
    for( size_t i = 0; i < 1000; ++i ) {
        std::stringstream ss;
        
        ss << "key" << i;
        
        
        std::string k(ss.str());
        const int *x = ht.find( k );
        
        if( x != 0 ) {
            std::cout << "find " << k << " " << *x << "\n";
        } else {
            std::cout << "meeeeep\n";
        }
        
        if( i % 2 == 0 ) {
            ht.remove( k );
            
        }
        
    }
    ht.print_stat();
    return 0;   
}
