/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(Position position, Color::value color, bool isPinned) : myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Position position, Color::value color) : myPosition(position), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position) : myPosition(position), myColor(Color::WHITE), myIsPinned(false)
{
}

Piece::Piece() : myPosition(), myColor(Color::WHITE), myIsPinned(false)
{
}

