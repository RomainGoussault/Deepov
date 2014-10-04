/*
 * Bishop.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Bishop : public Piece
{
public:

    Bishop(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
};

inline std::ostream& operator<<(std::ostream &strm, const Bishop &bishop)
{
	strm << "Bishop" << std::endl;
	return strm;
}

#endif /* BISHOP_HPP_ */
