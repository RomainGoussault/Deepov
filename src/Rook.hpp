/*
 * Rook.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"



class Rook : public Piece
{
public:

    Rook(Position position, Color::value color);
    std::vector<Move> getPseudoLegalMoves();

private:

};

inline std::ostream& operator<<(std::ostream &strm, const Piece &piece)
{
	strm << "Rook" << std::endl;
	return strm;
}

#endif /* ROOK_HPP_ */
