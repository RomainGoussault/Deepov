/*
 * Piece.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#include "Piece.hpp"
#include "Board.hpp"

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

std::vector<Move> Piece::getLegalMoves(Board &board)
{
	std::vector<Move> moves = getPseudoLegalMoves(board);

	// get rid of the non legal moves
	moves.erase(std::remove_if(moves.begin(), moves.end(),
			[board](Move move) mutable { return !board.isMoveLegal(move); }), moves.end());
	//TODO make this easier to understand..

	return moves;
}
