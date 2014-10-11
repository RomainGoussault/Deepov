/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"

Board::Board() : myPieces(), myColorToPlay(WHITE)
{
	/*for(int i = 0; i < 8; ++i )
	{
	    for(int j = 0; j < 8; ++j )
	    {
			Position position(i,j);
			Piece piece(position);
			myPieces[i][j] = piece;
	    }
	}*/
}

int Board::getTurn() const
{
    return myColorToPlay;
}

void Board::executeMove(Move move)
{
    myColorToPlay = (myColorToPlay+1) % 2;
}

void Board::addPiece(Piece piece, Position position)
{
   	myPieces[position.getX()][position.getY()].reset(new Piece(piece));
}

void Board::addPiece(Piece piece)
{
    addPiece(piece, piece.getPosition());
}

bool Board::isPositionFree(Position position)
{
    return myPieces[position.getX()][position.getY()] == nullptr;
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

std::shared_ptr<Piece> Board::getPiece(Position position)
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
            std::shared_ptr<Piece> piece;
            piece = myPieces[position.getX()][position.getY()];
            if (piece && piece->getColor() == color)
            {
                piecesList.push_back(*piece);
            }
        }
    }

    return piecesList;
}

std::vector<Piece> Board::getEnnemyPieces(int color)
{
    return getPieces((color + 1)%2);
}
