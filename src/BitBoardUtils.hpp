/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BITBOARDUTILS_HPP_
#define BITBOARDUTILS_HPP_

#include <vector>
#include <iostream>
#include <math.h>
#include <sstream>
#include <chrono>

#include "Types.hpp"
#include "Tables.hpp"

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
    #ifdef NO_POPCNT
    return popcount64sparse(U64 bitboard);
    #else
	return __builtin_popcountll(bitboard);
	#endif
}

// SWAR algorithm for 64 bits
inline unsigned int popcount64swar(U64 i)
{
  i = i - ((i >> 1) & 0x5555555555555555);
  i = (i & 0x3333333333333333) + ((i >> 2) & 0x3333333333333333);
  return (((i + (i >> 4)) & 0x0f0f0f0f0f0f0f0f) *
          0x0101010101010101) >> 56;
}

// "Brian Kernighan's way" https://chessprogramming.wikispaces.com/Population+Count
// efficient for sparse bitboard
inline unsigned int popcount64sparse(U64 bitboard)
{
   int count = 0;
   while (bitboard) {
       count++;
       bitboard &= bitboard - 1; // reset LS1B
   }
   return count;
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
void printBitBoard(const U64 &bitBoard);

inline bool isBitSet(const U64 bitBoard, const unsigned int x, const unsigned int y)
{
	unsigned int shift = 8*y + x;

	return (0 | 1LL << shift) & bitBoard;
}

inline bool areAligned(const Square s1, const Square s2, const Square s3) {
  return Tables::LINE_BB[s1][s2] & Tables::SQUARE_BB[s3];
}

double measurePopcntSpeed(U64 testBB, unsigned int (*f)(U64));

};

//Operator overload for Bitboard and Square
inline U64 operator&(U64 b, Square s) {
	return b & Tables::SQUARE_BB[s];
}

inline U64 operator|(U64 b, Square s) {
  return b | Tables::SQUARE_BB[s];
}

inline U64 operator^(U64 b, Square s) {
  return b ^ Tables::SQUARE_BB[s];
}

inline U64& operator&=(U64& b, Square s) {
  return b &= Tables::SQUARE_BB[s];
}

inline U64& operator|=(U64& b, Square s) {
  return b |= Tables::SQUARE_BB[s];
}

inline U64& operator^=(U64& b, Square s) {
  return b ^= Tables::SQUARE_BB[s];
}

#endif /* BITBOARDUTILS_HPP_ */
