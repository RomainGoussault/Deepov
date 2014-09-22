/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"
#include "Position.hpp"


Piece::Piece(Position position, int color, bool isPinned) : myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Position position, int color) : myPosition(position), myColor(color), myIsPinned(false)
{
}
