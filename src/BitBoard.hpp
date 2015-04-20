/*
 * Bitboard.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef BITBOARD_HPP_
#define BITBOARD_HPP_

typedef uint64_t U64;

//Note: We should use Little-Endian Rank-File Mapping

class Bitboard {
public:

	Bitboard(Position position, int color);

private:

	U64 whitePawns;
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
};

inline std::ostream& operator<<(std::ostream &strm, const Bitboard &bitboard) {
	strm << "Bitboard " << std::endl;
	return strm;
}

#endif /* BITBOARD_HPP_ */
