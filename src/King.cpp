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

std::vector<Move> King::getPseudoLegalMoves(Board &board)
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
	
	if(board.isQueenSideCastlingAllowed(myColor))
	{
		//Todo needs to check if the positions between the rook and the king are empty AND not attacked

		Move possibleMove = Move(myPosition, Position(6,myPosition.getY()));
		possibleMove.setIsCastling();
		kingMoves.push_back(possibleMove);
	}

	if(board.isKingSideCastlingAllowed(myColor))
	{
		Move possibleMove = Move(myPosition, Position(2,myPosition.getY()));
		possibleMove.setIsCastling();
		kingMoves.push_back(possibleMove);
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

bool King::isQueenSideCastlingPossible(const Board &board)
{
	int y = myColor == WHITE ? 0 : 7 ;

	//We already know the rook and the king has not moved
	bool iQSCP = true;
		//check if the positions are not in check
	/*	List<Position> positions = new ArrayList<>();
		positions.add(new Position(2,y));
		positions.add(new Position(3,y));
		positions.add(new Position(4,y));

		for(Position position : positions)
		{
			isQueenSideCastlingPossible = isQueenSideCastlingPossible && !board.isPositionAttacked(position, myColor);
		}*/
/*
	iQSCP = iQSCP && !board.isPositionAttacked(Position(2,y), myColor);

	Position p(1,y);
	iQSCP = iQSCP && board.isPositionFree(p);
		isQueenSideCastlingPossible = isQueenSideCastlingPossible && board.isPositionFree(Position(2,y));
	//	isQueenSideCastlingPossible = isQueenSideCastlingPossible && board.isPositionFree(new Position(3,y));
*/
	return iQSCP;
}

