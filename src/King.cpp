/*
 * King.hpp
 *
 *  Created on: 9 oct. 2014
 *      Author: Romain & Navid
 */

#include "King.hpp"


King::King(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> King::getPseudoLegalMoves(Board &board)
{
	std::vector<Move> kingMoves;
	std::vector<Position> destinations;
	PiecePtr otherPiece;

	destinations.push_back(myPosition.deltaXY(0,1));
	destinations.push_back(myPosition.deltaXY(0,-1));
	destinations.push_back(myPosition.deltaXY(1,-1));
	destinations.push_back(myPosition.deltaXY(1,0));
	destinations.push_back(myPosition.deltaXY(1,1));
	destinations.push_back(myPosition.deltaXY(-1,-1));
	destinations.push_back(myPosition.deltaXY(-1,0));
	destinations.push_back(myPosition.deltaXY(-1,1));

	for(std::vector<Position>::const_iterator i = destinations.begin(); i != destinations.end(); ++i)
	{
		Position destination = *i;

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
	//Todo needs to check if the positions between the rook and the king are empty AND not attached
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
