/*
 * Rook.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#include "Rook.hpp"
#include "Board.hpp"

Rook::Rook(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Rook::getPseudoLegalMoves(Board &board)
{
    std::vector<Move> rookMoves;

    int i = 1;
    Position destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            rookMoves.push_back(possibleMove);
        }
        else
        {
            Piece otherPiece = board.getPiece(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                rookMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(i);
    }

    return rookMoves;
}
