/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include "Board.hpp"
#include "Utils.hpp"

    /*********************************** Constructor ****************************************/
Board::Board() : myPieces(), myColorToPlay(WHITE), myMoves(), myEnPassant(), myCastling(), myMovesCounter()
{
}

Board::Board(std::string fen) : myPieces(), myColorToPlay(WHITE), myMoves(), myEnPassant(), myCastling(), myMovesCounter()
{
    std::vector<PiecePtr> piecesPtrs;

	std::vector<std::string> spaceSplit;
	std::vector<std::string> piecesByRank;

	boost::split(spaceSplit, fen, boost::is_any_of(" "));
	boost::split(piecesByRank, spaceSplit[0], boost::is_any_of("/"));

	int rank = 7;
	for (int i=0; i<8; i++)
	{
		std::vector<PiecePtr> piecesOnRank = Utils::getPieces(piecesByRank[i], rank);
		piecesPtrs.insert(piecesPtrs.end(), piecesOnRank.begin(), piecesOnRank.end());
		rank--;
	}

    for( std::vector<PiecePtr>::const_iterator i = piecesPtrs.begin(); i != piecesPtrs.end(); ++i)
    {
		addPiece(*i);
    }

    if (spaceSplit[1][0] == 'w')
    {
        myColorToPlay=WHITE;
    }
    else if (spaceSplit[1][0] == 'b')
    {
        myColorToPlay=BLACK;
    }

    for (int i=0; i<3; ++i)
    {
        myCastling[i] = false;
    }

    Utils::getCastling(spaceSplit[2],myCastling);

    if (spaceSplit[3][0] == '-')
    {
        myEnPassant=boost::optional<Position>();
    }
    else
    {
        myEnPassant=boost::optional<Position>(Utils::getSquare(spaceSplit[3]));
    }

    // I put a condition in case the FEN format doesn't include the move counters
    if (spaceSplit.size() >= 5)
    {
        myMovesCounter[0] = Utils::convertStringToInt(spaceSplit[4]);
    }
    else
    {
        myMovesCounter[0] = 0;
    }

    if (spaceSplit.size() >= 6)
    {
        myMovesCounter[1] = Utils::convertStringToInt(spaceSplit[5]);
    }
    else
    {
        myMovesCounter[1] = 0;
    }


}

    /******************************* Pieces manipulation ************************************/

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

    /******************************** Moves manipulation ************************************/

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

    /*********************************** Get attributes **************************************/

int Board::getTurn() const
{
    return myColorToPlay;
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

bool Board::getCastling(int castleNumber)
{
    return myCastling[castleNumber];
}

int Board::getMovesCounter(int color)
{
    return myMovesCounter[color];
}

    /******************************* Position manipulation ***********************************/

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
