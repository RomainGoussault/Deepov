
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
#ifdef _MSC_VER
#  include <nmmintrin.h>
#  define __builtin_popcountll _mm_popcnt_u64
#endif

inline bool moreThanOne(U64 bitboard)
{
	return bitboard & (bitboard-1);
}

/* Bit Hacks*/
// Source : https://graphics.stanford.edu/~seander/bithacks.html
inline unsigned int popcount(U64 bitboard)
{
	return __builtin_popcountll(bitboard);
}

//Some relevant links on this function:
// https://chessprogramming.wikispaces.com/BitScan
// http://stackoverflow.com/questions/671815/
// http://stackoverflow.com/questions/20713017/
//https://github.com/mcostalba/Stockfish/blob/master/src/bitboard.h#L305
inline Square msb(const U64 bitboard)
{
#ifdef _MSC_VER
	unsigned long idx;
	_BitScanReverse64(&idx, bitboard);
	return (Square)idx;

#else
	U64 idx;
	__asm__("bsrq %1, %0": "=r"(idx) : "rm"(bitboard));

#endif
	
	return (Square) idx;
	//return static_cast<Square>(__builtin_ctzll(bitboard));
}

inline Square lsb(U64 bitboard) { // Assembly code by Heinz van Saanen
#ifdef _MSC_VER
	unsigned long idx;
	_BitScanForward64(&idx, bitboard);
	return (Square)idx;

#else
	U64 idx;
	__asm__("bsfq %1, %0": "=r"(idx): "rm"(bitboard) );
	return (Square)idx;

#endif
}

inline Square pop_lsb(U64* b) {
	const Square s = lsb(*b);
	*b &= *b - 1;
	return s;
}

namespace BitBoardUtils
{
U64 inBetween(unsigned int sq1, unsigned int sq2);
void printBitBoard(const U64 &bitBoard);

inline bool isBitSet(const U64 bitBoard, const unsigned int x, const unsigned int y)
{
	unsigned int shift = 8*y + x;

	return (0 | 1LL << shift) & bitBoard;
}
};


#endif /* BITBOARDUTILS_HPP_ */
