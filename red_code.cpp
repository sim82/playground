/*
 * Copyright (C) 2011 Simon A. Berger
 *
 *  This program is free software; you may redistribute it and/or modify its
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 */


#include <algorithm>
#include <bitset>
#include <iostream>
#include <cassert>
#include <cmath>

#include <boost/dynamic_bitset.hpp>

float randf() {
	return float(std::rand()) / RAND_MAX;
}

int sample_ideal_soliton( const int N ) {
	while(true) {
		int k = 1 + std::rand() % N;
		if( k == 1 && randf() <= 1.0/N) {
			return k;
		} else if( randf() <= 1.0 / (k*(k-1))) {
			return k;
		}
	}
}

//int sample_robust_soliton( const int N, const float c = 0.2, const float delta = 0.5 ) {
//
//	const float R = c * log(N/delta) * sqrt(N);
//
//	//const float R = N / float(M);
//
//	while(true) {
//		int k = 1 + std::rand() % N;
//		if( k < (N/R) && randf() <= R/(k*N)) {
//			return k;
//		} else if( k == int(N/R) && randf() < R * log(R/delta) / N ) {
//			return k;
//		}
//	}
//}

int sample_robust_soliton( const int N, const int dM = 10, const float delta = 0.5 ) {

//	const float R = c * log(N/delta) * sqrt(N);

	//const float R = N / float(M);
	const int M = N / dM;
	const float R = N / float(M);
	while(true) {
		int k = 1 + std::rand() % N;
		if( k < M && randf() <= 1.0/(k*M)) {
			return k;
		} else if( k == M && randf() < log(R/delta) / M ) {
			return k;
		}
	}
}


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


class rand_without_replacement {
public:
	rand_without_replacement( const size_t nmax, int seed ) : rnd_list_(nmax) {
		srand(seed);
		for( size_t i = 0; i < nmax; ++i ) {
			rnd_list_[i] = i;
		}
		std::random_shuffle( rnd_list_.begin(), rnd_list_.end() );
	}

	int next() {
		assert( !rnd_list_.empty());
		int r = rnd_list_.back();
		rnd_list_.pop_back();
		return r;
	}
private:
	std::vector<size_t> rnd_list_;

};

template<size_t message_size, size_t num_blocks>
class lt_encoder {
public:
    const static size_t block_size = message_size / num_blocks;
    
    typedef std::vector<bool> message_t;
    typedef std::vector<bool> block_t;
    
    
    lt_encoder( const message_t &msg ) : message_(msg), seed_(std::rand()) {}

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
        
       // size_t degree = 1 + (std::rand() % 2);
        //size_t degree = sample_ideal_soliton(num_blocks);
        size_t degree = sample_robust_soliton(num_blocks);
        
//         if( std::rand() % 2 == 0 ) {
//             degree = 1;
//         }
        
        assert( degree >= 1 );
        assert( degree <= num_blocks );
        



        seed_ = std::rand();

        rand_without_replacement rwor(num_blocks, seed_);
        packet<block_size> packet(degree, seed_);
        

//        std::cout << "send: ";
        for( size_t i = 0; i < degree; ++i ) {
         
            size_t block_index = rwor.next();
//            std::cout << block_index << " ";
            packet.xor_block( get_block(block_index) );
        }
//        std::cout << "\n";
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


        rand_without_replacement rwor(num_blocks, p.get_seed());

//        std::cout << "recv: ";
        for( size_t i = 0; i < degree; ++i ) {
         
            index_list_.push_back( rwor.next() );
//            std::cout << index_list_.back() << " ";
        }
//        std::cout << "\n";
        
        
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
        const size_t init_degree = degree;
        
        
        if( degree > 1 ) {
            filter_against_full_packets( &dpacket );
            
            degree = dpacket.get_degree();
             
        }
        size_t nelim = 0;
        if( degree == 1 ) {

        	std::vector<dec_packet_t> new_full;
        	new_full.push_back( std::move(dpacket));

        	while( !new_full.empty() ) {
//        		std::cout << "match full packet: " <<  new_full.back().get_index() << "\n";

        		full_packets_.push_back(std::move( new_full.back() ));
        		new_full.pop_back();
        		match_full_packet(full_packets_.back(), &new_full);
//        		std::cout << "new full: " << new_full.size() << "\n";
        		nelim++;
        	}
            
            //full_packets_.push_back( std::move(dpacket) );
        } else {
         
            packet_store_.push_back( std::move(dpacket) );
        }
        std::cout << "nelim: " << nelim << " " << init_degree << "\n";
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
         
//            std::cout << "missing: " << n << "\n";
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
    
    void match_full_packet( const dec_packet_t &dpacket, std::vector<dec_packet_t> *ret_prom ) {
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
            
            ret_prom->push_back( std::move( packet_store_.at(*it) ));
            packet_store_.erase( packet_store_.begin() + (*it) );
        }
    }
    
private:
    
    std::vector<dec_packet_t> packet_store_;
    std::vector<dec_packet_t> full_packets_;
};


int main() {
    const size_t NBS = 128;
    const size_t MS = NBS * 1024;
    

//    while(true) {
//    	std::cout << sample_robust_soliton(32) << "\n";
//    }
    
    std::vector<bool> message(MS);
    
    //message[666] = true;
    
    for( auto it = message.begin(); it < message.end(); it += 3 ) {
            
        *it = true;
    }

    srand( time(0) );
    //std::cout << random() << "\n";
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
