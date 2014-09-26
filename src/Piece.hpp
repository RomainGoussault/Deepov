/*
 * Piece.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef Piece_HPP_
#define Piece_HPP_

#include "Position.hpp"
#include "Color.hpp"


class Piece
{
public:

	Piece(Position position, Color::value color, bool isPinned);
	Piece(Position position, Color::value color);
	Piece(Position position);
	Piece();
	Position getPosition();

private:

	Position myPosition;
	Color::value myColor;
	bool myIsPinned;
};


#endif /* Piece_HPP_ */
