/*
 * FastBoard.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef FASTBOARD_HPP_
#define FASTBOARD_HPP_

#include <cstdint>
#include <iostream>
#include <bitset>

//#include "Utils.hpp"
#define _RankSize_ 8
#define _BoardSize_ 64  // rename afterBoard.hpp is removed
typedef std::uint64_t U64;

//Note: We should use Little-Endian Rank-File Mapping

class FastBoard {
public:

	FastBoard();

//private:

	U64 myWhitePawns;
	U64 myWhiteKnights;
	U64 myWhiteBishops;
	U64 myWhiteRooks;
	U64 myWhiteQueens;
	U64 myWhiteKing;

	U64 myBlackPawns;
	U64 myBlackKnights;
	U64 myBlackBishops;
	U64 myBlackRooks;
	U64 myBlackQueens;
	U64 myBlackKing;

	U64 myWhitePieces;
	U64 myBlackPieces;
	U64 myAllPieces;
};

inline std::ostream& operator<<(std::ostream &strm, const FastBoard &fastBoard) {
	std::bitset<64> x(fastBoard.myWhitePawns);
	std::bitset<64> y(fastBoard.myWhiteKnights);
	strm << "FastBoard " << x << std::endl;
	strm << "FastBoard " << y << std::endl;

	return strm;
}

#endif /* FASTBOARD_HPP_ */
