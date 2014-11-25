/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"
#include "Utils.hpp"

/*****************************  Constructors *********************************/
Board::Board() : myPieces(), myColorToPlay(WHITE), myMoves()
{
}

Board::Board(std::string fen) : myPieces(), myColorToPlay(WHITE), myMoves()
{
	std::vector<PiecePtr> piecePtrs = Utils::getPiecesFromFen(fen);

    for( std::vector<PiecePtr>::const_iterator i = piecePtrs.begin(); i != piecePtrs.end(); ++i)
    {
		addPiece(*i);
    }
}

/******************************************************************************/

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

    //pieceToMove.incrementMoveCounter(); TODO???
    executeMove(pieceToMove, destination);

	//TODO:
	//Handle promotion/castling/en Passant

    myMoves.push_back(move);
    myColorToPlay = (myColorToPlay+1) % 2;
}

void Board::undoMove(Move move)
{
    Position origin = move.getOrigin();
	Position destination = move.getDestination();

	PiecePtr capturePiecePtr = move.getCapturedPiece();
	bool isCaptureMove = capturePiecePtr!= nullptr;
	PiecePtr pieceToMove = getPiecePtr(destination);
	std::cout << "Piece to move: " << pieceToMove << std::endl;

    executeMove(pieceToMove, origin);
    //pieceToMove.incrementMoveCounter(); TODO???

	if(isCaptureMove)
    {
		//add the captured piece
        addPiece(capturePiecePtr);
	}

	//TODO:
	//Handle promotion/castling/en Passant
	
	//Remove the last move from the myMoves list.
    myMoves.pop_back();
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

std::vector<PiecePtr> Board::getPieces(int color)
{
    std::vector<PiecePtr> piecesList;

    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            Position position(i,j);
            PiecePtr piece;
            piece = myPieces[position.getX()][position.getY()];
            if (piece && piece->getColor() == color)
            {
                piecesList.push_back(piece);
            }
        }
    }

    return piecesList;
}

std::vector<PiecePtr> Board::getEnemyPieces(int color)
{
    return getPieces((color + 1)%2);
}

boost::optional<Move> Board::getEnemyLastMove()
{
    if (myMoves.size()>0)
    {
        return boost::optional<Move>(myMoves[myMoves.size()-1]);
    }
    else
    {
        return boost::optional<Move>();
    }
}

bool Board::isFirstMove()
{
    if (myMoves.size()==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
