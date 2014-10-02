/*
 * Move.hpp
 *
 *  Created on: 26 sept. 2014
 *      Author: Romain
 */

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include <memory>
#include "Position.hpp"

class Piece;

class Move
{
public:

	Position myOrigin;
	Position myDestination;
	std::shared_ptr<Piece> myCapturedPiece;
	bool myIsPromotion;

	Piece getCapturedPiece();
    void setCapturedPiece(Piece &piece);
	Move(Position origin, Position destination);

private:

};

inline std::ostream& operator<<(std::ostream &strm, const Move &move)
{
	strm << "Orig: "  << move.myOrigin  << "  Dest: "  << move.myDestination<< std::endl;
	return strm;
}

#endif /* MOVE_HPP_ */
