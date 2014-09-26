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

	Piece(char value, Position position, Color::value color, bool isPinned);
	Piece(char value, Position position, Color::value color);
	Piece(char value, Position position);
	Piece();
	Position getPosition();
	char getValue();
	bool isNull();

private:

	char myValue;
	Position myPosition;
	Color::value myColor;
	bool myIsPinned;
};


#endif /* Piece_HPP_ */
