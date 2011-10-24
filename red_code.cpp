#include <algorithm>
#include <bitset>
#include <iostream>
#include <cassert>
#include <boost/dynamic_bitset.hpp>

std::vector<bool> & operator^=( std::vector<bool> &op1, const std::vector<bool> &op2 ) {
 
    assert( op1.size() == op2.size() );
    
    auto first1 = op1.begin();
    auto last1 = op1.end();
    
    auto first2 = op2.begin();
    
    for( ;first1 != last1; ++first1, ++first2 ) {
        *first1 = *first1 ^ *first2;
    }
    
    return op1;
}

template<size_t block_size>
class packet {
public:
    typedef std::vector<bool> block_t;
    
    packet( size_t degree, size_t seed ) : degree_(degree), seed_(seed), block_(block_size) {}
    
    void xor_block( const block_t &block ) {
        block_ ^= block;
    }
    const block_t &get_block() const {
     
        return block_;
        
    }
    
    
    size_t get_seed() const {
        return seed_;
    }
    
    size_t get_degree() const {
        return degree_;
    }
    
private:
    size_t degree_;
    size_t seed_;
    block_t block_;    
};

template<size_t message_size, size_t num_blocks>
class lt_encoder {
public:
    const static size_t block_size = message_size / num_blocks;
    
    typedef std::vector<bool> message_t;
    typedef std::vector<bool> block_t;
    
    
    lt_encoder( const message_t &msg ) : message_(msg), seed_(1234) {}
    
    block_t get_block( size_t block ) {
     
        assert( block < num_blocks );
        
        auto start = message_.begin() + (block_size * block);
        auto end = message_.begin() + (block_size * (block+1));
        
        assert( start >= message_.begin() );
        assert( end <= message_.end() );
        return block_t( start, end );
        
    }
    
    
    packet<block_size> gen_packet() {
        std::srand(seed_);
//         size_t degree = 1 + (std::rand() % num_blocks);
        
        size_t degree = 1 + (std::rand() % 2);
        
        
//         if( std::rand() % 2 == 0 ) {
//             degree = 1;
//         }
        
        assert( degree >= 1 );
        assert( degree <= num_blocks );
        

        seed_ = std::rand();
        packet<block_size> packet(degree, seed_);
        
        
        std::srand(seed_);
        for( size_t i = 0; i < degree; ++i ) {
         
            size_t block_index = std::rand() % num_blocks;
            
            packet.xor_block( get_block(block_index) );
        }
        
        return packet;
        
    }
    
private:
    const message_t message_;
    size_t seed_;
    
    
  
};


template<size_t block_size>
class dec_packet {
public:
    typedef dec_packet<block_size> dec_packet_t;
    typedef std::vector<bool> block_t;
    
    dec_packet( const packet<block_size> &p, size_t num_blocks ) 
    : block_(p.get_block() )
    {
    
        const size_t degree = p.get_degree();
        std::srand( p.get_seed() );
        for( size_t i = 0; i < degree; ++i ) {
         
            index_list_.push_back( std::rand() % num_blocks );
        }
        
        
    }
    
    void filter( const dec_packet_t &other ) {
     
        assert( other.index_list_.size() == 1 );
        
        size_t index = other.index_list_.front();
        
        while( index_list_.size() > 1 ) {
         
            auto it = std::find( index_list_.begin(), index_list_.end(), index );
            
            if( it == index_list_.end() ) {
                break;   
            }
            
            block_ ^= other.block_;
            
            index_list_.erase( it );
            //std::cout << "filter erasing: " << other.get_index() << "\n";
        }
    }
    
    size_t get_degree() const {
     
        return index_list_.size();
    }
    
    size_t get_index() const {
     
        assert( index_list_.size() == 1 );
        
        return index_list_.front();
    }
    
    const block_t &get_block() const {
        return block_;
    }
    
private:
    block_t block_;
    std::vector<size_t> index_list_;
    
    
};

template<size_t message_size, size_t num_blocks>
class lt_decoder {
    
public:
    const static size_t block_size = message_size / num_blocks;
    
    typedef std::vector<bool> message_t;
    typedef std::vector<bool> block_t;
    typedef dec_packet<block_size> dec_packet_t;
    
    
    message_t receive_packet( const packet<block_size> &packet ) {
     
        
        dec_packet_t dpacket( packet, num_blocks );
        size_t degree = dpacket.get_degree();

        
        
        if( degree > 1 ) {
            filter_against_full_packets( &dpacket );
            
            degree = dpacket.get_degree();
             
        }
        
        if( degree == 1 ) {
            std::cout << "full packet: " << dpacket.get_index() << "\n";
            match_full_packet(dpacket);
            
            full_packets_.push_back( std::move(dpacket) );
        } else {
         
            packet_store_.push_back( std::move(dpacket) );
        }

        return decode();
        
    }
    
    message_t decode() {
     
        std::bitset<num_blocks> s;
        
        size_t n = num_blocks;
        
        std::vector<dec_packet_t *> dps;
        
        for( dec_packet_t & dp : full_packets_ ) {
            size_t index = dp.get_index();
            
            if( !s[index] ) {
             
                --n;
                dps.push_back( &dp );
                s[index] = true;
            }
            
        }
        
        if( n != 0 ) {
         
            std::cout << "missing: " << n << "\n";
            return message_t();
        }
        
        message_t message(message_size);
        
        for( dec_packet_t * dp : dps ) {
            size_t index = dp->get_index();
            
            auto start = message.begin() + block_size * index;
            auto end = message.begin() + block_size * (index+1);
            
            
            
            assert( start >= message.begin() );
            assert( end <= message.end() );
        
            const block_t &block = dp->get_block();
            std::copy( block.begin(), block.end(), start );
        }
    
        return message;
    }
    
    void filter_against_full_packets( dec_packet_t *dpacket ) {
     
        assert( dpacket->get_degree() > 1 );
        
        for( const dec_packet_t & fp : full_packets_ ) {
            dpacket->filter( fp );
 
            if( dpacket->get_degree() == 1 ) {
                break;
            }
            
        }
    }
    
    void match_full_packet( const dec_packet_t &dpacket ) {
        assert( dpacket.get_degree() == 1 );
        
        std::vector<size_t> promote;
        
        for( size_t i = 0; i < packet_store_.size(); ++i ) {
         
            
            dec_packet_t &dp = packet_store_.at(i);
            
            dp.filter( dpacket );
            
            if( dp.get_degree() == 1 ) {
                promote.push_back( i );
            }
        }
        
        for( auto it = promote.rbegin(); it != promote.rend(); ++it ) {
            assert( *it < packet_store_.size() );
            
            full_packets_.push_back( std::move( packet_store_.at(*it) ));
            packet_store_.erase( packet_store_.begin() + (*it) );
        }
    }
    
private:
    
    std::vector<dec_packet_t> packet_store_;
    std::vector<dec_packet_t> full_packets_;
};


int main() {
    const size_t NBS = 32;
    const size_t MS = NBS * 1024;
    
    
    std::vector<bool> message(MS);
    
    //message[666] = true;
    
    for( auto it = message.begin(); it < message.end(); it += 3 ) {
            
        *it = true;
    }
    
    lt_encoder<MS,NBS> lte(message);
    lt_decoder<MS,NBS> ltd;
    
    
    size_t iter = 0;
    while( true ) {
        packet<1024> packet(lte.gen_packet());
        
        std::vector<bool> rec = ltd.receive_packet( packet );
        
        ++iter;
        if( rec.size() == MS ) {
            std::cout << "equal: " << (message == rec) << "\n";
            std::cout << "num: " << iter << "\n";
//             std::copy( rec.begin(), rec.end(), std::ostream_iterator<bool>(std::cout) );
//             std::cout << "\n";
            break;
        }
    }
    
    
}