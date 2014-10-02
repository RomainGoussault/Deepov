/*
 * Move.hpp
 *
 *  Created on: 26 sept. 2014
 *      Author: Romain
 */

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include "Position.hpp"

class Move
{
public:

	Position myOrigin;
	Position myDestination;
	//Piece myCapturedPiece;
	bool myIsPromotion;

	Move(Position origin, Position destination);

private:

};

#endif /* MOVE_HPP_ */
