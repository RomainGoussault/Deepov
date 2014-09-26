/*
 * Board.cpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#include "Board.hpp"

Board::Board()
{
}

void Board::addPiece(Piece piece, int position)
{
	myPieces[position] = piece;
}

