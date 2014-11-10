
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
/*    Piece otherPiece;

    // Direction +x
    int i = 1;
    Position destination = myPosition.deltaX(i);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            Piece otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction +x+y

    destination = destination.deltaY(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction +y
    destination = myPosition.deltaX(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction -x+y
    destination = myPosition.deltaX(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction -x
    destination = myPosition.deltaY(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction -x-y
    destination = myPosition.deltaY(-i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction -y
    destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }

    //Direction -y+x
    destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            kingMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                kingMoves.push_back(possibleMove);
            }
        }
    }
*/
    return kingMoves;
}
