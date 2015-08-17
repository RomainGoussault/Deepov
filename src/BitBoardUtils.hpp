
#ifndef BITBOARDUTILS_HPP_
#define BITBOARDUTILS_HPP_

#include <vector>
#include <iostream>
#include <math.h>
 #include <sstream>

#include "Types.hpp"

#ifndef _U64
typedef std::uint64_t U64;
#define _U64
#endif // _U64


namespace BitBoardUtils
{
	U64 inBetween(unsigned int sq1, unsigned int sq2);
	std::string printBitBoard(const U64 &bitBoard);

	/* Bit Hacks*/
	// Source : https://graphics.stanford.edu/~seander/bithacks.html
	inline unsigned int countBBBitsSet(const U64 bitboard)
	{
		return __builtin_popcountll(bitboard);
	}

	//Some relevant links on this function:
	// https://chessprogramming.wikispaces.com/BitScan
	// http://stackoverflow.com/questions/671815/
	// http://stackoverflow.com/questions/20713017/
	//https://github.com/mcostalba/Stockfish/blob/master/src/bitboard.h#L305
	inline Square getMsbIndex(const U64 bitboard)
	{
		  U64 idx;
		  __asm__("bsrq %1, %0": "=r"(idx): "rm"(bitboard) );
		  return (Square) idx;
//		return static_cast<Square>(__builtin_ctzll(bitboard));
	}

	inline Square lsb(U64 b) { // Assembly code by Heinz van Saanen
		U64 idx;
		__asm__("bsfq %1, %0": "=r"(idx): "rm"(b) );
		return (Square) idx;
	}

	inline Square pop_lsb(U64* b) {
		const Square s = lsb(*b);
		*b &= *b - 1;
		return s;
	}

	inline bool isBitSet(const U64 bitBoard, const unsigned int x, const unsigned int y)
	{
		unsigned int shift = 8*y + x;

		return (0 | 1LL << shift) & bitBoard;
	}
};


#endif /* BITBOARDUTILS_HPP_ */
