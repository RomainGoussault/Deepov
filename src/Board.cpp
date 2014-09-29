/*
 * Board.cpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */
#include <iostream>

#include "Board.hpp"

Board::Board() : myPieces()
{
}

void Board::addPiece(Piece piece, Position position)
{
	myPieces[position.getX()][position.getY()] = piece;
}

void Board::addPiece(Piece piece)
{
	addPiece(piece, piece.getPosition());
}

bool Board::isPositionFree(Position position)
{
	return getPiece(position).isEmpty();
}

bool Board::isPositionOnBoard(Position position)
{
	char x = position.getX();
	char y = position.getY();

	if (x > BOARD_SIZE || y > BOARD_SIZE)
	{
		return false;
	}

	if (x < 0 || y < 0)
	{
		return false;
	}

	return true;
}

Piece Board::getPiece(Position position)
{
	return myPieces[position.getX()][position.getY()];
}

std::vector<Move> Board::getPseudoLegalMoves(Piece piece)
{
	return piece.getPseudoLegalMoves();
}
