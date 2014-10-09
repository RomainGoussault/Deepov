/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"

Board::Board() : myPieces(), colorToPlay(0)
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

    if (x >= BOARD_SIZE || y >= BOARD_SIZE)
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

std::vector<Piece> Board::getPieces(int color)
{
    std::vector<Piece> piecesList;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            Position position(i,j);
            Piece thePiece;
            thePiece = myPieces[position.getX()][position.getY()];
            if (thePiece.getColor() == color)
            {
                piecesList.push_back(thePiece);
            }
        }
    }

    return piecesList;
}

std::vector<Piece> Board::getEnnemyPieces(int color)
{
    return getPieces((color + 1)%2);
}
