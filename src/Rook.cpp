/*
 * Rook.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#include "Rook.hpp"

Rook::Rook(Position position, Color::value color) : Piece(position, color)
{
}

std::vector<Move> Rook::getPseudoLegalMoves()
{
	std::vector<Move> rookMoves;
	//TODO Implement

	Position origin(0, 0);
	Position destination(0, 0);
	Move move(origin, destination);

	rookMoves.push_back(move);

	return rookMoves;
}
