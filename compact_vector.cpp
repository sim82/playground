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

#include <vector>
#include <limits>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <math.h>

template<size_t N, typename base_type = uint64_t>
class compact_vector {

    const static size_t base_size = sizeof(base_type) * 8;
    typedef std::vector<base_type> base_vec;


public:



    struct reference_impl {


        typename base_vec::iterator base_;
        uint8_t shift_;
        base_type emask_;


        reference_impl( typename base_vec::iterator base, uint8_t shift, base_type emask ) : base_(base), shift_(shift), emask_(emask) {}

        operator base_type() const
        {

            base_type v = (*base_ >> shift_) & emask_;

            if( shift_ + N > base_size ) {
                size_t second_shift = base_size - shift_;
                v |= (*(base_+1) << second_shift) & emask_;
            }

            return v;
        }

        reference_impl&
        operator=(base_type v)
        {

			base_type vs = v << shift_;
			base_type ms = emask_ << shift_;
			*base_ = *base_ ^ ((*base_ ^ vs) & ms); // from http://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge

			if( shift_ + N > base_size ) {
				size_t second_shift = base_size - shift_;

				vs = v >> second_shift;
				ms = emask_ >> second_shift;
				*(base_+1) = *(base_+1) ^ ((*(base_+1) ^ vs) & ms);

			}



            return *this;
        }



    };


    struct iterator_impl : public std::iterator<std::random_access_iterator_tag, base_type>{

        typedef reference_impl  reference;
        typedef reference_impl* pointer;
        typedef iterator_impl   iterator;

        typename base_vec::iterator base_;
        int8_t shift_;
        base_type emask_;

        iterator_impl( typename base_vec::iterator base, uint8_t shift, base_type emask ) : base_(base), shift_(shift), emask_(emask) {

        }

        iterator_impl &operator++() {
        	//shift_ += N;
//        	base_ += shift_ / base_size;
//        	shift_ %= base_size;
            if( shift_ + N >= base_size ) {
                ++base_;
                shift_ = (shift_ + N) % base_size;
            } else {
            	shift_ += N;
            }
            return *this;
        }

        iterator_impl &operator--() {
            if( shift_ < ptrdiff_t(N) ) {
                --base_;
                shift_ = base_size - N + shift_;
            } else {
                shift_ -= N;
            }
            return *this;
        }

        iterator_impl &operator+=(ptrdiff_t d) {
        	if( d == 0 ) {
        		return *this;
        	}

        	const ptrdiff_t bitd = N * d;



        	base_ += bitd / ptrdiff_t(base_size);

        	if( d > 0 ) {
        		shift_ += bitd % ptrdiff_t(base_size);

        		if( shift_ >= ptrdiff_t(base_size) ) {
        			++base_;
        			shift_ -= base_size;
        		}
        	} else {
        		shift_ += bitd % ptrdiff_t(-base_size);

        		if( shift_ < 0 ) {
        			--base_;
        			shift_ += base_size;
        		}
        	}

        	std::cout << "op+: " << bitd << " " << &(*base_) << " " << int(shift_) << "\n";

			return *this;
        }

        iterator_impl &operator-=(ptrdiff_t d) {
        	return operator+=(-d);
        }

        iterator_impl operator+(ptrdiff_t d) {
        	iterator_impl tmp = *this;
        	return tmp += d;
        }

        iterator_impl operator-(ptrdiff_t d) {
        	return operator+(-d);
        }



        reference_impl operator*() {
            return reference(base_, shift_, emask_);
        }

        bool operator==( const iterator_impl &other ) const {
//            std::cout << "compare: " << &(*base_) << ":" << int(shift_) << " " << &(*other.base_) << ":" << int(other.shift_) << "\n";

            return (base_ == other.base_) && (shift_ == other.shift_);
        }

        bool operator!=( const iterator_impl &other ) const {
            return !(*this == other);
        }

    };

    struct const_iterator_impl : private iterator_impl {
        typedef base_type  const_reference;


        const_iterator_impl( const iterator_impl &iter ) : iterator_impl(iter) {

        }

        const_reference operator*() const {
            return const_reference(reference(iterator_impl::base_, iterator_impl::shift_, iterator_impl::emask_));
        }

        using iterator_impl::operator++;
        using iterator_impl::operator--;
        using iterator_impl::operator==;
        using iterator_impl::operator!=;
    };



    typedef base_type                                    value_type;
	typedef size_t                                       size_type;
	typedef ptrdiff_t                                    difference_type;
	typedef reference_impl                               reference;
	typedef base_type                                    const_reference;
	typedef reference_impl*                              pointer;
	typedef const base_type*                             const_pointer;
	typedef iterator_impl                                iterator;
	typedef const_iterator_impl                          const_iterator;
	typedef std::reverse_iterator<const_iterator>        const_reverse_iterator;
	typedef std::reverse_iterator<iterator>              reverse_iterator;


    compact_vector( size_type s ) : size_(s), base_(to_base_size(s)), emask_(emask(N)){

//    	for( size_t i = 0; i < base_size; ++i ) {
//    		emask_shifted_[i] = emask_ << i;
//    	}

        base_type x = -1;
        if( x < 0 ) {
            throw std::runtime_error( "base_type is signed" );
        }

        if( pow(2,N) - 1 > std::numeric_limits<base_type>::max() ) {
            throw std::runtime_error( "base_type too small" );
        }
    }


//    void set( size_type off, base_type v ) {
//        size_type first_bit = off * N;
//        size_type last_bit = (off+1) * N - 1;
//
//        size_type first_base = base_off( first_bit );
//        size_type last_base = base_off( last_bit );
//
//
//        size_type first_shift = first_bit % base_size;
//
//        base_type &fb = base_[first_base];
//
//        base_type vs = v << first_shift;
//        base_type ms = emask_ << first_shift;
//        fb = fb ^ ((fb ^ vs) & ms);
//
////         ^= ~(emask_ << first_shift);
//
//      //  base_[first_base] ^= base_[first_base] & (emask_ << first_shift);
//        base_[first_base] |= (v & emask_) << first_shift;
//
//
//
//        if( first_base != last_base ) {
//            size_type second_shift = base_size - first_shift;
//
//            base_[last_base] &= ~(emask_ >> second_shift);
//            base_[last_base] |= (v & emask_) >> second_shift;
//        }
//    }
//
//    base_type get( size_type off ) {
//        size_type first_bit = off * N;
//        size_type last_bit = (off+1) * N - 1;
//
//        size_type first_base = base_off( first_bit );
//        size_type last_base = base_off( last_bit );
//
//        size_type first_shift = first_bit % base_size;
//        base_type v = (base_[first_base] >> first_shift) & emask_;
//
//        if( first_base != last_base ) {
//            size_type second_shift = base_size - first_shift;
//            v |= (base_[last_base] << second_shift) & emask_;
//        }
//
//        return v;
//    }

    size_type size() const {
        return size_;
    }

    size_type getn() const {
        return N;
    }

    iterator begin() {
        return iterator( base_.begin(), 0, emask_ );
    }

    iterator end() {
        size_type last_bit = size_ * N;


        size_type base = base_off( last_bit );
        size_type shift = last_bit % base_size;


        return iterator( base_.begin() + base, shift, emask_ );
    }


    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_iterator begin() const {
        return iterator( base_.begin(), 0, emask_ );
    }

    const_iterator end() const {
        size_type last_bit = size_ * N;


        size_type base = base_off( last_bit );
        size_type shift = last_bit % base_size;


        return iterator( base_.begin() + base, shift, emask_ );
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator( end() );
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator( begin() );
    }


    reference operator[](size_type n)
	{
	  //return *(begin() + n);
    	size_type boff = n * N;

    	return reference( base_.begin() + boff / base_size, boff % base_size, emask_ );
	}

	const_reference	operator[](size_type n) const
	{
		size_type boff = n * N;
		return reference( base_.begin() + boff / base_size, boff % base_size, emask_ );
	}


	void resize( size_type s ) {
		 base_.resize(to_base_size(s));
		 size_ = s;
	}

	size_type allocated_bytes() {
		return base_.size() * sizeof(base_type);
	}

private:




    size_type to_base_size( size_type n ) {
        return (n * N) / (base_size) + 1;
    }

    size_type base_off( size_type bit ) {
        return bit / base_size;
    }

    const static base_type emask( size_type n ) {
        base_type mask = 0;
        for( size_type i = 0; i < n; ++i ) {
            mask <<= 1;
            mask |= 1;
        }

        return mask;
    }


    size_type size_;
    base_vec base_;
    base_type emask_;

//    base_type emask_shifted_[base_size];

};

template<size_t N>
class rander {


public:
    rander() : mod_(int(pow(2,N)) - 1 ) {}

    size_t operator()() {
        return std::rand() % mod_;
    }

private:
    const size_t mod_;

};


int main() {
	const size_t N = 5;
	const size_t s = 1000 * 1000;
	compact_vector<N,uint64_t> cv(s);
	std::vector<uint64_t> ref(s);

	std::vector<uint64_t> rnd1(s * 100);
	std::vector<uint64_t> rnd2(s * 100);

	std::generate(rnd1.begin(), rnd1.end(), rander<32>());
	std::generate(rnd2.begin(), rnd2.end(), rander<5>());


	std::cout << "start\n";
	for( size_t i = 0; i < s * 100; ++i ) {
		size_t idx = rnd1[i] % s;
		uint64_t r = rnd2[i];

		cv[idx] = r;
		ref[idx] = r;
	}


	std::cout << "size: " << cv.allocated_bytes() << "\n";

	bool eq = std::equal( cv.begin(), cv.end(), ref.begin() );

	std::cout << "eq: " << eq << "\n";
}

int main4() {
	const size_t N = 5;
	compact_vector<N,uint64_t> cv(1000);

	for( size_t i = 0; i < cv.size(); ++i ) {
		cv[i] = i;
	}

	compact_vector<N,uint64_t>::iterator it = cv.end() - 1;

	//std::cout << *it << " " << *(it+2) << "\n";


	for( size_t i = 0 ; i < 20; ++i ) {
		std::cout << *it << "\n";
		it -= 2;
		//++it;
	}

	return 1;

}

int main3() {
    const size_t N = 5;



  //  compact_vector<N,uint64_t> ref(1000 * 1000);
    std::vector<int> ref( 1000 * 1000 );


    compact_vector<N,uint64_t> cv(ref.size());
    //std::vector<uint8_t> cv(ref.size());




    std::generate( ref.begin(), ref.end(), rander<N>() );


    for( size_t i = 0; i < 100; ++i ) {
        std::copy( ref.begin(), ref.end(), cv.rbegin());


        //std::cout << i << "\n";
    }

    bool eq = std::equal( ref.rbegin(), ref.rend(), cv.begin() );

    std::cout << "equal: " << eq << "\n";


    //std::copy( cv.begin(), cv.end(), std::ostream_iterator<int>(std::cout, " " ));
    std::cout << "\n";

    return 0;
}


//int main2() {
//    const size_t N = 9;
//
//    compact_vector<N,uint64_t> cv(1000 * 1000);
//    std::vector<uint64_t> ref( cv.size(), 0 );
//
//    for( size_t i = 0; i < cv.size() * 10; ++i ) {
//
//        size_t idx = std::rand() % cv.size();
//
//        ref[idx] = std::rand() % (int(pow(2,N)) - 1);
//
//       // cv.set(idx,ref[idx]);
//        cv[idx] = ref[idx];
//
//    }
//
//    for( size_t i = 0; i < cv.size(); ++i ) {
//        std::cout << i << " " << i * cv.getn() << ": " << int(cv.get(i)) << " " << ref[i] << "\n";
//        if( cv[i] != ref[i] ) {
//            std::cout << "meeeep\n";
//        }
//
//    }
//
//    return 0;
//
//}
