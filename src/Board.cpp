/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"

Board::Board() : myPieces(), myColorToPlay(WHITE), myMoves()
{
}

int Board::getTurn() const
{
    return myColorToPlay;
}

void Board::executeMove(Move move)
{
    Position origin = move.getOrigin();
	Position destination = move.getDestination();
	PiecePtr capturePiecePtr = move.getCapturedPiece();
	bool isCaptureMove = capturePiecePtr!= nullptr;
	PiecePtr pieceToMove = getPiecePtr(origin);

	if(isCaptureMove)
    {
		//remove the captured piece
        removePiece(capturePiecePtr->getPosition());

    }

    //pieceToMove.incrementMoveCounter(); TODO
    executeMove(pieceToMove, destination);

	//TODO:
	//Handle promotion/castling/en Passant

    myMoves.push_back(move);
    myColorToPlay = (myColorToPlay+1) % 2;
}

void Board::executeMove(PiecePtr piecePtr, Position destination)
{
    removePiece(piecePtr->getPosition());
    piecePtr->setPosition(destination);
    addPiece(piecePtr);
}

void Board::addPiece(PiecePtr piecePtr, Position position)
{
   	 myPieces[position.getX()][position.getY()] = piecePtr;
}

void Board::addPiece(PiecePtr piecePtr)
{
    addPiece(piecePtr, piecePtr->getPosition());
}

void Board::removePiece(Position position)
{
    //TODO: Findout why following line does not work.
  //  PiecePtr p = getPiecePtr(position);
   // p.reset();
   // std::cout << " p " << p << std::endl;
    myPieces[position.getX()][position.getY()].reset();
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

PiecePtr Board::getPiecePtr(Position position) const
{
	PiecePtr p = myPieces[position.getX()][position.getY()];

    return p;
}

std::vector<Piece> Board::getPieces(int color)
{
    std::vector<Piece> piecesList;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            Position position(i,j);
            PiecePtr piece;
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
