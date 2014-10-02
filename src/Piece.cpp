/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(Position position, Color::value color, bool isPinned) : myIsEmpty(false), myPosition(position), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Position position, Color::value color) : myIsEmpty(false), myPosition(position), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position) : myIsEmpty(false), myPosition(position), myColor(Color::WHITE), myIsPinned(false)
{
}

Piece::Piece() : myIsEmpty(true), myPosition(), myColor(Color::WHITE), myIsPinned(false)
{
}

Position Piece::getPosition()
{
	return myPosition;
}

bool Piece::isEmpty()
{
	return myIsEmpty;
}

std::vector<Move> Piece::getPseudoLegalMoves(Board &board)
{
	std::vector<Move> emptyVector;
	return emptyVector;
}
