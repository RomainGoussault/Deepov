/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece() : myPosition(), myIsEmpty(true), myColor(WHITE), myIsPinned(false)
{
}

Piece::Piece(Position position) : myPosition(position), myIsEmpty(true), myColor(WHITE), myIsPinned(false)
{
}

Piece::Piece(Position position, int color) : myPosition(position), myIsEmpty(false), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position, int color, bool isPinned) : myPosition(position), myIsEmpty(false), myColor(color), myIsPinned(isPinned)
{
}

Position Piece::getPosition() const
{
    return myPosition;
}

int Piece::getColor() const
{
    return myColor;
}

bool Piece::isEmpty() const
{
    return myIsEmpty;
}

bool Piece::areColorDifferent(Piece &piece)
{
    return myColor != piece.getColor();
}
