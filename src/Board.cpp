/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"

Board::Board() : myPieces()
{
}

void Board::init()
{
	for(int i = 0; i < 8; ++i )
	{
	    for(int j = 0; j < 8; ++j )
	    {
			Position position(i,j);
			Piece piece(position);
			myPieces[i][j] = piece;
	    }
	}
}

void Board::addPiece(Piece piece, Position position)
{
   	std::cout << "ADD PIECE: "<< position  << std::endl;
	std::cout<< "Piece [0,7] " << myPieces[0][7] << std::endl;

   	myPieces[position.getX()][position.getY()] = piece;

	std::cout<< "Piece [0,7] " << myPieces[0][7] << std::endl;
	std::cout << myPieces[0][7] << std::endl;
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
