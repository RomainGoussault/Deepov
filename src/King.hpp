
/*
 * King.hpp
 *
 *  Created on: 09 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef KING_HPP_
#define KING_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"
#include "Board.hpp"

class King : public Piece
{
public:

    King(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
    std::vector<Position> getAttackedPositions(Board &board);
    char getChar() const {return 'k';};
};

inline std::ostream& operator<<(std::ostream &strm, const King &king)
{
	strm << "King " << static_cast<const Piece &>(king) << std::endl;
	return strm;
}

#endif /* KING_HPP_ */
