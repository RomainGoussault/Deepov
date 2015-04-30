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
#include <vector>

//#include "Utils.hpp"
#define _RankSize_ 8
#define _BoardSize_ 64  // rename afterBoard.hpp is removed
typedef std::uint64_t U64;

#include "FastMove.hpp"
#include "LookUpTables.hpp"

//Note: We should use Little-Endian Rank-File Mapping

class FastBoard {
public:

	FastBoard();

	/* Get the bitboards */

    U64 getWhitePawns() const;
	U64 getWhiteKnights() const;
	U64 getWhiteBishops() const;
	U64 getWhiteRooks() const;
	U64 getWhiteQueens() const;
	U64 getWhiteKing() const;

	U64 getBlackPawns() const;
	U64 getBlackKnights() const;
	U64 getBlackBishops() const;
	U64 getBlackRooks() const;
	U64 getBlackQueens() const;
	U64 getBlackKing() const;

	U64 getWhitePieces() const;
	U64 getBlackPieces() const;
	U64 getAllPieces() const;
	U64 getPieces(const int color) const {return color == 0 ? getWhitePieces() : getBlackPieces();}

	/*  **********  */

	/* Moves methods */

    U64 kingPseudoLegalMoves(const int& color, const U64& kingPos) const;
    U64 queenPseudoLegalMoves(const int& color, const U64& kingPos) const;
    U64 bishopPseudoLegalMoves(const int& color, const U64& kingPos) const;
    U64 rookPseudoLegalMoves(const int& color, const U64& kingPos) const;
    U64 knightPseudoLegalMoves(const int& color, const U64& kingPos) const;
    U64 pawnPseudoLegalMoves(const int& color, const U64& kingPos) const;
    std::vector<FastMove> getMoves() const;

	/* ************* */

private:

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

	std::vector<FastMove> myMoves;
};

inline std::ostream& operator<<(std::ostream &strm, const FastBoard &fastBoard) {
	std::bitset<64> x(fastBoard.getWhitePawns());
	std::bitset<64> y(fastBoard.getWhiteKnights());
	strm << "FastBoard " << x << std::endl;
	strm << "FastBoard " << y << std::endl;

	return strm;
}

#endif /* FASTBOARD_HPP_ */
