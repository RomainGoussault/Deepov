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


typedef std::uint64_t U64;

//Note: We should use Little-Endian Rank-File Mapping

class FastBoard {
public:

	FastBoard();

//private:

	U64 myWhitePawns;
	U64 whiteKnights;
	U64 whiteBishops;
	U64 whiteRooks;
	U64 whiteQueens;
	U64 whiteKing;

	U64 blackPawns;
	U64 blackKnights;
	U64 blackBishops;
	U64 blackRooks;
	U64 blackQueens;
	U64 blackKing;

	U64 whitePieces;
	U64 blackPieces;
	U64 allPieces;
};

inline std::ostream& operator<<(std::ostream &strm, const FastBoard &fastBoard) {
	std::bitset<64> x(fastBoard.myWhitePawns);
	strm << "FastBoard " << x << std::endl;


	return strm;
}

#endif /* FASTBOARD_HPP_ */
