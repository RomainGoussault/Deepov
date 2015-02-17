/*
 * Board.cpp
 *
 *  Cdreated on: 24 sept. 2014
 *   ar   Author: Romain
 */
#include <memory>
#include <cassert>

#include "Board.hpp"
#include "Utils.hpp"
#include "King.hpp"


/*********************************** Constructor ****************************************/
Board::Board() : myPieces(), myColorToPlay(WHITE), myMoves(), myEnPassant(), myCastling(), myMovesCounter(), myHalfMovesCounter()
{
}

Board::Board(std::string fen) : myPieces(), myColorToPlay(WHITE), myMoves(), myEnPassant(), myCastling(), myMovesCounter(), myHalfMovesCounter()
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

	for(std::vector<PiecePtr>::const_iterator i = piecesPtrs.begin(); i != piecesPtrs.end(); ++i)
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
		myEnPassant=boost::optional<Position>(Utils::getPosition(spaceSplit[3]));
	}

	// I put a condition in case the FEN format doesn't include the move counters
	if (spaceSplit.size() >= 5)
	{
		myMovesCounter = std::stoi(spaceSplit[4]);
	}
	else
	{
		myMovesCounter = 0;
	}

	if (spaceSplit.size() >= 6)
	{
		myHalfMovesCounter = std::stoi(spaceSplit[5]);
	}
	else
	{
		myHalfMovesCounter = 0;
	}
}

/******************************* Pieces manipulation ************************************/

void Board::addPiece(PiecePtr piecePtr, Position position)
{
	//A piece should be added on a FREE position only
	assert(isPositionFree(position));

	myPieces[position.getX()][position.getY()] = piecePtr;
}

void Board::addPiece(PiecePtr piecePtr)
{
	addPiece(piecePtr, piecePtr->getPosition());
}

void Board::removePiece(Position position)
{
	//There should be a piece to be removed
	assert(!isPositionFree(position));

	myPieces[position.getX()][position.getY()].reset();
}

/******************************** Moves manipulation ************************************/

bool Board::isFirstMove() const
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

	if(move.isCastling())
	{
		movePiece(pieceToMove, destination);
        if (destination.getX()== 6)
        {
            Position rookOrigin(7, destination.getY());
            Position rookDestination(5, destination.getY());
            movePiece(getPiecePtr(rookOrigin),rookDestination);
        }
        else if (destination.getX() == 2)
        {
            Position rookOrigin(7, destination.getY());
            Position rookDestination(5, destination.getY());
            movePiece(getPiecePtr(rookOrigin),rookDestination);
        }
	}
	else if(move.isPromotion())
	{
		if(isCaptureMove)
		{
			//remove the captured piece
			removePiece(capturePiecePtr->getPosition());
		}

        removePiece(pieceToMove->getPosition());
        addPiece(move.getPromotedPiece());
	}
	else
	{
		if(isCaptureMove)
		{
			//remove the captured piece
			removePiece(capturePiecePtr->getPosition());
		}

		//pieceToMove.incrementMoveCounter(); TODO???
		movePiece(pieceToMove, destination);
	}

	//updateCastlingRights();

	myMoves.push_back(move);
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);
}

void Board::undoMove(Move move)
{
	Position origin = move.getOrigin();
	Position destination = move.getDestination();

	PiecePtr capturePiecePtr = move.getCapturedPiece();
	bool isCaptureMove = capturePiecePtr!= nullptr;
	PiecePtr pieceToMove = getPiecePtr(destination);

	if(move.isCastling())
	{
		//TODO
		std::cout << " NOT IMPLEMENTED" << std::endl;
	}
	else if(move.isPromotion())
	{
		//TODO
		std::cout << " NOT IMPLEMENTED" << std::endl;
	}
	else
	{
		movePiece(pieceToMove, origin);
		//pieceToMove.incrementMoveCounter(); TODO???

		if(isCaptureMove)
		{
			//add the captured piece
			addPiece(capturePiecePtr);
		}
	}

	//updateCastlingRights();

	//Remove the last move from the myMoves list.
	myMoves.pop_back();
	myColorToPlay = Utils::getOppositeColor(myColorToPlay);
}

void Board::movePiece(PiecePtr piecePtr, Position destination)
{
	removePiece(piecePtr->getPosition());
	piecePtr->setPosition(destination);
	addPiece(piecePtr);
}

boost::optional<Move> Board::getEnemyLastMove() const
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

//Returns true if the queen side rook AND the king has not moved during this game
bool Board::isQueenSideCastlingAllowed(const int color) const
{
	return myCastling[1 + 2*color];
}

//Returns true if the king side rook AND the king has not moved during this game
bool Board::isKingSideCastlingAllowed(const int color) const
{
	return myCastling[2*color];
}

/*********************************** Get attributes **************************************/

int Board::getColorToPlay() const
{
	return myColorToPlay;
}

PiecePtr Board::getPiecePtr(const Position position) const
{
	PiecePtr p = myPieces[position.getX()][position.getY()];
	return p;
}

std::vector<PiecePtr> Board::getPieces(const int color) const
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

std::vector<PiecePtr> Board::getEnemyPieces(const int color) const
{
	int ennemyColor = Utils::getOppositeColor(color);
	return getPieces(ennemyColor);
}

PiecePtr Board::getKing(const int color) const
{
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			Position position(i,j);
			PiecePtr piecePtr = myPieces[position.getX()][position.getY()];

			if (piecePtr != nullptr && piecePtr->getColor() == color)
			{
				std::shared_ptr<King> kingPtr = std::dynamic_pointer_cast<King>(piecePtr);

				if(kingPtr != nullptr)
				{
					return kingPtr;
				}
			}
		}
	}

	std::cout << " ERROR could not find king"; // TODO throw exception
	return nullptr;
}

Position Board::getKingPosition(const int color) const
{
	return getKing(color)->getPosition();
}

std::vector<Move> Board::getMoves() const
{
	return myMoves;
}

boost::optional<Position> Board::getEnPassantPosition() const
{
	return myEnPassant;
}

bool Board::getCastling(const int castleNumber) const
{
	return myCastling[castleNumber];
}

int Board::getHalfMovesCounter() const
{
	return myHalfMovesCounter;
}

int Board::getMovesCounter() const
{
	return myMovesCounter;
}

std::vector<Position> Board::getAttackedPositions(const int color) const
{
	std::vector<PiecePtr> piecePtrs = getPieces(color);
	std::vector<Position> attackedPositions;

	for (const auto ennemyPiecePtr : piecePtrs)
	{
		std::vector<Position> pieceAttackedPositions = ennemyPiecePtr->getAttackedPositions(*this);
		attackedPositions.insert(attackedPositions.end(), pieceAttackedPositions.begin(), pieceAttackedPositions.end());
	}

	return attackedPositions;
}

std::vector<Move> Board::getLegalMoves()
{
	return getLegalMoves(myColorToPlay);
}

std::vector<Move> Board::getLegalMoves(int color)
{
	std::vector<PiecePtr> pieces = getPieces(color);
	std::vector<Move> legalMoves;

	for(const auto piece : pieces)
	{
		std::vector<Move> pieceLegalMoves = piece->getLegalMoves(*this);
		legalMoves.insert(legalMoves.end(), pieceLegalMoves.begin(), pieceLegalMoves.end());
	}

	return legalMoves;
}

/******************************* Position manipulation ***********************************/

bool Board::isPositionFree(const Position position) const
{
	return myPieces[position.getX()][position.getY()] == nullptr;
}

bool Board::isPositionOnBoard(const Position position) const
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

bool Board::isPositionAttacked(const Position position, const int color) const
{
	std::vector<Position> attackedPositions = getAttackedPositions(color);
	// TODO attackedPositions should be an attribute of the board class, that we update on each execute/undo move

	return std::count(attackedPositions.begin(), attackedPositions.end(), position) > 0;
}

/*********************************** Perft *******************************************/

int Board::perft(int depth)
{
	int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

	std::vector<Move> moves = getLegalMoves();

	for (const auto move : moves)
	{
		executeMove(move);
		nodes += perft(depth - 1);
		undoMove(move);
	}

	return nodes;
}

int Board::divide(int depth)
{
	int nMoves;
	int nodes = 0;
	int nodeTotal = 0;

	if (depth == 0)
	{
		return 1;
	}

	std::vector<Move> moves = getLegalMoves();
	nMoves = moves.size();

	for (const auto move : moves)
	{
		std::cout << std::endl;
		executeMove(move);
		nodes = perft(depth - 1);
		std::cout <<  move.toShortString() <<  " " << nodes << std::endl;
		nodeTotal += nodes;
		undoMove(move);
	}

	std::cout << std::endl;
	std::cout << "Total nodes: " << nodeTotal << std::endl;
	std::cout << "Total moves: " << nMoves << std::endl;
	return nodes;
}

bool Board::isMoveLegal(const Move move)
{
	bool isLegalMove = true;
	int color = myColorToPlay;

	executeMove(move);

	if(isCheck(color))
	{
		isLegalMove = false;
	}

	undoMove(move);

	return isLegalMove;
}

bool Board::isCheck(const int color) const
{
	int ennemyColor = Utils::getOppositeColor(color);

	std::vector<Position> ennemyAttackingPositions = getAttackedPositions(ennemyColor);
	Position kingPosition = getKingPosition(color);

	if(std::find(ennemyAttackingPositions.begin(), ennemyAttackingPositions.end(), kingPosition) != ennemyAttackingPositions.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
