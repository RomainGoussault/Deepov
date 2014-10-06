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

    Rook(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
};

inline std::ostream& operator<<(std::ostream &strm, const Rook &rook)
{
    if(rook.isEmpty())
    {
        return strm;
    }

	strm << "Rook " << static_cast<const Piece &>(rook) << std::endl;
	return strm;
}

#endif /* ROOK_HPP_ */
