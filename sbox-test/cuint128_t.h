#pragma once
#include <iostream>
class cuint128_t
{
public:
	// class elements
	uint64_t hi;
	uint64_t lo;



	// class defination
	
	cuint128_t() {
		hi = 0 ;
		lo = 0 ;
	}
	cuint128_t(const uint64_t hi, const uint64_t lo)
	: hi(hi), lo(lo) {
	}
	
	cuint128_t(const uint64_t lo)
	: hi(0),lo(lo) {
	}

	cuint128_t& operator<<(const int shift) {
		if (shift < 64) {
			hi = (hi >> shift) | lo << (shift - 64);
			lo = lo >> shift;
		}
		else {
			hi = lo << (shift - 64);
			lo = 0;
		}
		return *this;
	}

	cuint128_t& operator^(const cuint128_t rhs) {
		cuint128_t out;
		out.hi = this->hi ^ rhs.hi;
		out.lo = this->lo ^ rhs.lo;
		return out;
	}

	cuint128_t& operator&(const cuint128_t rhs) {
		cuint128_t out;
		out.hi = this->hi & rhs.hi;
		out.lo = this->lo & rhs.lo;
		return out;
	}

	cuint128_t& operator~() {
		this->hi = ~this->hi;
		this->lo = ~this->lo;
		return *this;
	}


};