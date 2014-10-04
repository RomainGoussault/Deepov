/*
 * Bishop.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */

#include "Bishop.hpp"
#include "Board.hpp"

Bishop::Bishop(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Bishop::getPseudoLegalMoves(Board &board)
{
    std::vector<Move> bishopMoves;
    Piece otherPiece;

    // Direction +x +y
    int i = 1;
    Position destination = myPosition.deltaX(i);
    destination = destination.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            bishopMoves.push_back(possibleMove);
        }
        else
        {
            Piece otherPiece = board.getPiece(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                bishopMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(i);
        destination = destination.deltaY(i);
    }

    //Direction +x-y
    i = 1;
     destination = myPosition.deltaX(i);
     destination = destination.deltaY(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            bishopMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiece(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                bishopMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(i);
        destination = destination.deltaY(-i);
    }

    //Direction -x+y
    i = 1;
        destination = myPosition.deltaX(-i);
        destination = destination.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            bishopMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiece(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                bishopMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(-i);
        destination = destination.deltaY(i);
    }

    //Direction -x-y
    i = 1;
    destination = myPosition.deltaX(-i);
    destination = destination.deltaY(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            bishopMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiece(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                bishopMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(-i);
        destination = destination.deltaY(-i);
    }

    return bishopMoves;
}
