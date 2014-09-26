/*
 * Board.cpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#include "Board.hpp"
#include "Position.hpp"

Board::Board()
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

