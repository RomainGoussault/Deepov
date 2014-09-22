/*
 * Piece.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef Piece_HPP_
#define Piece_HPP_

#include "Position.hpp"


class Piece
{
public:

	Piece(Position position, int color, bool isPinned);
	Piece(Position position, int color);

private:

	Position& myPosition;
	int myColor;
	bool myIsPinned;
};


#endif /* Piece_HPP_ */
