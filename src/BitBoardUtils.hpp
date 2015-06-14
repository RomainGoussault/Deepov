
#ifndef BITBOARDUTILS_HPP_
#define BITBOARDUTILS_HPP_

#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"

namespace BitBoardUtils
{
    U64 inBetween(int sq1, int sq2);

    /* Bit Hacks*/
    // Source : https://graphics.stanford.edu/~seander/bithacks.html
    inline unsigned int countBBBitsSet(U64 v)
    {
    	v = v - ((v >> 1) & (std::uint64_t)~(std::uint64_t)0/3);                           // temp
    	        v = (v & (std::uint64_t)~(std::uint64_t)0/15*3) + ((v >> 2) & (std::uint64_t)~(std::uint64_t)0/15*3);      // temp
    	        v = (v + (v >> 4)) & (std::uint64_t)~(std::uint64_t)0/255*15;                      // temp
    	        unsigned int c = (std::uint64_t)(v * ((std::uint64_t)~(std::uint64_t)0/255)) >> (sizeof(std::uint64_t) - 1) * CHAR_BIT; // count
    	        return c;
    }

    //Some relevant links on this function:
	// https://chessprogramming.wikispaces.com/BitScan
	// http://stackoverflow.com/questions/671815/
	// http://stackoverflow.com/questions/20713017/
	inline int getMsbIndex(const U64 bitboard) {return (63 - __builtin_clzll(bitboard));}

};


#endif /* BITBOARDUTILS_HPP_ */
