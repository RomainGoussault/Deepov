/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"

Piece::Piece(Position position, Color::value color, bool isPinned) : myPosition(position), myIsEmpty(true), myColor(color), myIsPinned(isPinned)
{
}

Piece::Piece(Position position, Color::value color) : myPosition(position), myIsEmpty(true), myColor(color), myIsPinned(false)
{
}

Piece::Piece(Position position) : myPosition(position), myIsEmpty(true),  myColor(Color::WHITE), myIsPinned(false)
{
}

Piece::Piece() : myPosition(),myIsEmpty(true),  myColor(Color::WHITE), myIsPinned(false)
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
