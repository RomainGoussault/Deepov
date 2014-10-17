/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece() : myPosition(), myColor(WHITE), myIsPinned(false)
{
}

Piece::Piece(Position position) : myPosition(position), myColor(WHITE), myIsPinned(false)
{
}

Piece::Piece(Position position, int color) : myPosition(position), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position, int color, bool isPinned) : myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Position Piece::getPosition() const
{
    return myPosition;
}

void Piece::setPosition(Position position)
{
    myPosition = position;
}

int Piece::getColor() const
{
    return myColor;
}

bool Piece::areColorDifferent(Piece &piece) const
{
    return myColor != piece.getColor();
}
