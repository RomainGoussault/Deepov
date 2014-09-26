/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(char value, Position position, Color::value color, bool isPinned) : myValue(value), myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(char value, Position position, Color::value color) : myValue(value), myPosition(position), myColor(color), myIsPinned(false)
{
}

Piece::Piece(char value, Position position) : myValue(value), myPosition(position), myColor(Color::WHITE), myIsPinned(false)
{
}

Piece::Piece() : myValue(0), myPosition(), myColor(Color::WHITE), myIsPinned(false)
{
}

Position Piece::getPosition()
{
	return myPosition;
}

bool Piece::isNull()
{
	return myValue;
}

char Piece::getValue(){
	return myValue;
}



