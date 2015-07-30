
#ifndef BITBOARDUTILS_HPP_
#define BITBOARDUTILS_HPP_

#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"

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
	inline Square getMsbIndex(const U64 bitboard) {return static_cast<Square>(__builtin_ctzll(bitboard));}

	inline bool isBitSet(const U64 bitBoard, const unsigned int x, const unsigned int y)
	{
		unsigned int shift = 8*y + x;

		return (0 | 1LL << shift) & bitBoard;
	}
};


#endif /* BITBOARDUTILS_HPP_ */
