/*
 * Pawn.hpp
 */

#include "Pawn.hpp"

Pawn::Pawn(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Pawn::getPseudoLegalMoves(Board &board)
{
	std::vector<Move> pawnMoves;
	PiecePtr otherPiece;
	int direction = getDirection();

	/* Is starting pawn ? */

	if (isOnStartingRank())
	{
		if (board.isPositionFree(myPosition.deltaY(direction)) && board.isPositionFree(myPosition.deltaY(2*direction)))
		{
			Position destination(myPosition.deltaY(2*direction));
			Move possibleMove(myPosition,destination);
			pawnMoves.push_back(possibleMove);
		}
	}

	/* En passant ? */
	if (board.getMoves().size() == 0) /* If position comes from FEN i won't have a lastMove in the
        move vector. Ultimately with UCI we will only use this case. */
	{
		if (isEnPassantPossibleFEN(board))
		{
			Position enemyPawnPosition(board.getEnPassantPosition()->deltaY(-direction));
			Move possibleMove(myPosition,enemyPawnPosition.deltaY(direction));
			possibleMove.setCapturedPiece(board.getPiecePtr(enemyPawnPosition));
			pawnMoves.push_back(possibleMove);
		}
	}
	else
	{
		if (isEnPassantPossible(board))
		{
			Position enemyPawnPosition(board.getEnemyLastMove()->getDestination());
			Move possibleMove(myPosition,enemyPawnPosition.deltaY(direction));
			possibleMove.setCapturedPiece(board.getPiecePtr(enemyPawnPosition));
			pawnMoves.push_back(possibleMove);
		}
	}

	Position destination(myPosition.deltaY(direction));
	if (board.isPositionFree(destination))
	{
		if (isGoingToPromote())
		{
			std::vector<Move> promotionMoves(getPromotionMoves(destination));
			pawnMoves.insert(pawnMoves.end(), promotionMoves.begin(), promotionMoves.end());
		}
		else
		{
			Move possibleMove(myPosition,destination);
			pawnMoves.push_back(possibleMove);
		}
	}

	/* Capture ? (test the 2 sides)*/

	int i = 1;
	destination=myPosition.deltaXY(i,direction);

	if (board.isPositionOnBoard(destination))
	{
		otherPiece = board.getPiecePtr(destination);
		if (otherPiece != nullptr && areColorDifferent(*otherPiece))
		{
			if (isGoingToPromote())
			{
				std::vector<Move> promotionMoves(getPromotionMoves(destination));
				// Add captured piece to each move
				for (unsigned int j = 0; j < promotionMoves.size(); j++)
				{
					promotionMoves[j].setCapturedPiece(otherPiece);
				}
				pawnMoves.insert(pawnMoves.end(), promotionMoves.begin(), promotionMoves.end());
			}
			else
			{
				Move possibleMove(myPosition,destination);
				possibleMove.setCapturedPiece(otherPiece);
				pawnMoves.push_back(possibleMove);
			}
		}
	}

	i = -1;
	destination=myPosition.deltaXY(i,direction);

	if (board.isPositionOnBoard(destination))
	{
		otherPiece = board.getPiecePtr(destination);
		if (otherPiece != nullptr && areColorDifferent(*otherPiece))
		{
			if (isGoingToPromote())
			{
				std::vector<Move> promotionMoves(getPromotionMoves(destination));
				// Add captured piece to each move
				for (unsigned int j = 0; j < promotionMoves.size(); j++)
				{
					promotionMoves[j].setCapturedPiece(otherPiece);
				}
				pawnMoves.insert(pawnMoves.end(), promotionMoves.begin(), promotionMoves.end());
			}
			else
			{
				Move possibleMove(myPosition,destination);
				possibleMove.setCapturedPiece(otherPiece);
				pawnMoves.push_back(possibleMove);
			}
		}
	}

	return pawnMoves;
}

std::vector<Position> Pawn::getAttackedPositions(Board &board)
{
	std::vector<Position> attackedPositions;
	int direction = getDirection();

	Position destination = myPosition.deltaXY(-1, direction);
	if (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);
	}

	destination = myPosition.deltaXY(1, direction);
	if (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);
	}

	return attackedPositions;
}

/*****************************  Promotion functions *********************************/

std::vector<Move> Pawn::getPromotionMoves(Position const& destination)
{
	std::vector<Move> movesList;

	{Move possibleMove(myPosition,destination);
	possibleMove.setIsPromotion();
	possibleMove.setPromotedPawn(shared_from_this());

	possibleMove.setPromotedPiece('q');
	movesList.push_back(possibleMove);}

	{Move possibleMove(myPosition,destination);
	possibleMove.setIsPromotion();
	possibleMove.setPromotedPawn(shared_from_this());

	possibleMove.setPromotedPiece('r');
	movesList.push_back(possibleMove);}

	{Move possibleMove(myPosition,destination);
	possibleMove.setIsPromotion();
	possibleMove.setPromotedPawn(shared_from_this());

	possibleMove.setPromotedPiece('b');
	movesList.push_back(possibleMove);}

	{Move possibleMove(myPosition,destination);
	possibleMove.setIsPromotion();
	possibleMove.setPromotedPawn(shared_from_this());

	possibleMove.setPromotedPiece('n');
	movesList.push_back(possibleMove);}

	return movesList;
}

bool Pawn::isGoingToPromote() const
{
	if (myColor == WHITE) {
		return (myPosition.getY() == 6);
	}
	else {
		return (myPosition.getY() == 1);
	}
}

/*****************************  EnPassant functions *********************************/

bool Pawn::isOnGoodRankForEnPassant() const
{
	if (myColor == WHITE) {
		return (myPosition.getY() == 4);
	}
	else {
		return (myPosition.getY() == 3);
	}
}

bool Pawn::isEnPassantPossible(Board &board) const
{
	if (!isOnGoodRankForEnPassant())
	{
		return false;
	}
	else
	{
		boost::optional<Move> enemyLastMove(board.getEnemyLastMove());
		//bool isNotFirstMove = enemyLastMove; // True if there is a move in enemyLastMove

		if (enemyLastMove)
		{
			Position enemyMoveOrigin = enemyLastMove->getOrigin();
			Position enemyMoveDestination = enemyLastMove->getDestination();
			PiecePtr enemyPiece(board.getPiecePtr(enemyMoveDestination));

			std::shared_ptr<Pawn> isPawn = std::dynamic_pointer_cast<Pawn>(enemyPiece);
			// Convert to pawn shared pointer

			bool isEnemyPiecePawn(false);

			if (isPawn!=NULL) // if isPawn = NULL, enemyPiece was not a Pawn subclass of Piece
			{
				isEnemyPiecePawn = true;
			}

			bool isPlus2Move(std::abs(enemyMoveOrigin.getY() - enemyMoveDestination.getY()) == -2*getDirection());
			bool isOnNextColumn(std::abs(enemyMoveDestination.getX() - myPosition.getX()) == 1);

			return(isEnemyPiecePawn && isPlus2Move && isOnNextColumn);
		}
		else
		{
			return false;
		}
	}

	return false;
}

bool Pawn::isEnPassantPossibleFEN(Board &board) const
{
	if (!isOnGoodRankForEnPassant())
	{
		return false;
	}

	boost::optional<Position> enPassantCandidate(board.getEnPassantPosition());
	if (enPassantCandidate)
	{
		return(std::abs(enPassantCandidate->getX() - myPosition.getX()) == 1); // i.e. isOnNextColumn
	}
	else
	{
		return false;
	}
}

/*****************************  Other functions *********************************/

int Pawn::getDirection() const
{
	if (myColor == WHITE) {
		return 1;
	}
	else {
		return -1;
	}
}

bool Pawn::isOnStartingRank() const
{
	if (myColor == WHITE) {
		return (myPosition.getY() == 1);
	}
	else {
		return (myPosition.getY() == 6);
	}
}

bool Pawn::isOnLastRank() const
{
	if (myColor == WHITE) {
		return (myPosition.getY() == 7);
	}
	else {
		return (myPosition.getY() == 0);
	}
}
