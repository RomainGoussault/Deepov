/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(Position position, int color, bool isPinned) : myPosition(position), myIsEmpty(true), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Position position, int color) : myPosition(position), myIsEmpty(true), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position) : myPosition(position), myIsEmpty(true), myColor(WHITE), myIsPinned(false)
{
}

Piece::Piece() : myPosition(), myIsEmpty(true), myColor(WHITE), myIsPinned(false)
{
}

Position Piece::getPosition()
{
    return myPosition;
}

int Piece::getColor() const
{
    return myColor;
}

bool Piece::isEmpty()
{
    return myIsEmpty;
}

bool Piece::areColorDifferent(Piece &piece)
{
    return myColor != piece.getColor();
}

std::vector<Move> Piece::getPseudoLegalMoves(Board &board)
{
    std::vector<Move> emptyVector;
    return emptyVector;
}
