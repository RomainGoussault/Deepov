/*
 * King.hpp
 *
 *  Created on: 9 oct. 2014
 *      Author: Romain & Navid
 */

#include "King.hpp"
#include <array>


King::King(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> King::getPseudoLegalMoves(const Board &board)
{
	std::vector<Move> kingMoves;
	PiecePtr otherPiece;
	std::array<Position,8> destinations;

	destinations[0] = myPosition.deltaXY(0,1);
	destinations[1] = myPosition.deltaXY(0,-1);
	destinations[2] = myPosition.deltaXY(1,-1);
	destinations[3] = myPosition.deltaXY(1,0);
	destinations[4] = myPosition.deltaXY(1,1);
	destinations[5] = myPosition.deltaXY(-1,-1);
	destinations[6] = myPosition.deltaXY(-1,0);
	destinations[7] = myPosition.deltaXY(-1,1);

	for(const auto& destination : destinations)
	{
		if (board.isPositionOnBoard(destination))
		{
			Move possibleMove = Move(myPosition, destination);
			if (board.isPositionFree(destination))
			{
				kingMoves.push_back(possibleMove);
			}
			else
			{
				otherPiece = board.getPiecePtr(destination);
				// look for capture
				if (areColorDifferent(*otherPiece))
				{
					possibleMove.setCapturedPiece(otherPiece);
					kingMoves.push_back(possibleMove);
				}
			}
		}
	}
	
	if(isQueenSideCastlingPossible(board))
	{
		Move queenSideCastlingMove = Move(myPosition, Position(6, myPosition.getY()));
		queenSideCastlingMove.setIsCastling();
		kingMoves.push_back(queenSideCastlingMove);
	}

	if(isKingSideCastlingPossible(board))
	{
		Move kingSideCastlingMove = Move(myPosition, Position(2, myPosition.getY()));
		kingSideCastlingMove.setIsCastling();
		kingMoves.push_back(kingSideCastlingMove);
	}
	
    return kingMoves;
}

std::vector<Position> King::getAttackedPositions(const Board &board)
{
	std::vector<Position> attackedPositions;
	std::array<Position,8> destinations;

	destinations[0] = myPosition.deltaXY(0,1);
	destinations[1] = myPosition.deltaXY(0,-1);
	destinations[2] = myPosition.deltaXY(1,-1);
	destinations[3] = myPosition.deltaXY(1,0);
	destinations[4] = myPosition.deltaXY(1,1);
	destinations[5] = myPosition.deltaXY(-1,-1);
	destinations[6] = myPosition.deltaXY(-1,0);
	destinations[7] = myPosition.deltaXY(-1,1);

	for(const auto& destination : destinations)
	{
		if (board.isPositionOnBoard(destination))
		{
			attackedPositions.push_back(destination);
		}
	}

	return attackedPositions;
}

bool King::isQueenSideCastlingPossible(const Board &board) const
{
	//This return false if the queen side rook or the king has already moved
	bool iQSCP = board.isQueenSideCastlingAllowed(myColor);

	if(!iQSCP) return false;

	int y = myColor == WHITE ? 0 : 7 ;
	int ennemyColor = myColor == WHITE ? BLACK : WHITE;

	Position p2 = Position(2,y);
	iQSCP = iQSCP && !board.isPositionAttacked(p2, ennemyColor);
	iQSCP = iQSCP && !board.isPositionAttacked(Position(3,y), ennemyColor);
	iQSCP = iQSCP && !board.isPositionAttacked(Position(4,y), ennemyColor);

	iQSCP = iQSCP && board.isPositionFree(Position(1,y));
	iQSCP = iQSCP && board.isPositionFree(Position(2,y));
	iQSCP = iQSCP && board.isPositionFree(Position(3,y));

	return iQSCP;
}

bool King::isKingSideCastlingPossible(const Board &board) const
{
	//This return false if the king side rook or the king has already moved
	bool iKSCP = board.isKingSideCastlingAllowed(myColor);

	if(!iKSCP) return false;

	int y = myColor == WHITE ? 0 : 7 ;
	int ennemyColor = myColor == WHITE ? BLACK : WHITE;

	iKSCP = iKSCP && !board.isPositionAttacked(Position(4,y), ennemyColor);
	iKSCP = iKSCP && !board.isPositionAttacked(Position(5,y), ennemyColor);
	iKSCP = iKSCP && !board.isPositionAttacked(Position(6,y), ennemyColor);

	iKSCP = iKSCP && board.isPositionFree(Position(5,y));
	iKSCP = iKSCP && board.isPositionFree(Position(6,y));

	return iKSCP;
}
