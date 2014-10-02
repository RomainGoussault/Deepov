/*
 * Rook.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#include "Rook.hpp"

Rook::Rook(Position position, Color::value color) : Piece(position, color)
{
}

std::vector<Move> Rook::getPseudoLegalMoves(Board &board)
{
	std::vector<Move> rookMoves;
	//TODO Implement
/*

	Position origin();
	Position destination();
	Move move(origin, destination);

        i = 1;
		destination = myPosition.deltaX(i);
		while (board.isPositionOnBoard(destination))
		{
			possibleMove = new Move(position, destination);

			if (board.isPositionFree(destination))
			{
				pseudoLegalMoves.add(possibleMove);
			}
			else
			{
				Piece piece = board.getPiece(destination);
				// look for capture
				if (pieceToMove.areColorDifferent(piece))
				{
					possibleMove.setCapturedPiece(piece);
					pseudoLegalMoves.add(possibleMove);
				}
				break;
			}

			++i;
			destination = position.deltaX(i);
		}


*/








	return rookMoves;
}
