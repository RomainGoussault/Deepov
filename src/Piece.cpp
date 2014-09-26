/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(Type value, Position position, Color::value color, bool isPinned) : myValue(value), myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Type value, Position position, Color::value color) : myValue(value), myPosition(position), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Type value, Position position) : myValue(value), myPosition(position), myColor(Color::WHITE), myIsPinned(false)
{
}

Piece::Piece() : myValue(EMPTY), myPosition(), myColor(Color::WHITE), myIsPinned(false)
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

int Piece::getValue() const
{
	return myValue;
}



