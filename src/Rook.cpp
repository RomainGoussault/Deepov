/*
 * Rook.cpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#include "Rook.hpp"

Rook::Rook(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Rook::getRookMoves(Board &board, PiecePtr piecePtr)
{
    std::vector<Move> rookMoves;
    PiecePtr otherPiece;
    Position myPosition = piecePtr->getPosition();

    // Direction +x
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
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (piecePtr->areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                rookMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaX(i);
    }

    //Direction +y
    i = 1;
    destination = myPosition.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            rookMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (piecePtr->areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                rookMoves.push_back(possibleMove);
            }
            break;
        }

        ++i;
        destination = myPosition.deltaY(i);
    }

    //Direction -x
    i = -1;
    destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            rookMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (piecePtr->areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                rookMoves.push_back(possibleMove);
            }
            break;
        }

        --i;
        destination = myPosition.deltaX(i);
    }

    //Direction -y
    i = -1;
    destination = myPosition.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            rookMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr  (destination);
            // look for capture
            if (piecePtr->areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                rookMoves.push_back(possibleMove);
            }
            break;
        }

        --i;
        destination = myPosition.deltaY(i);
    }

    return rookMoves;
}

std::vector<Position> Rook::getAttackedPositions(Board &board, PiecePtr piecePtr)
{
    std::vector<Position> attackedPosition;
    PiecePtr otherPiece;
    Position myPosition = piecePtr->getPosition();

    // Direction +x
    int i = 1;
    Position destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
		attackedPosition.push_back(destination);

        if (!board.isPositionFree(destination))
        {
            break;
        }

        ++i;
        destination = myPosition.deltaX(i);
    }

    //Direction +y
    i = 1;
    destination = myPosition.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
		attackedPosition.push_back(destination);

        if (!board.isPositionFree(destination))
        {
            break;
        }

        ++i;
        destination = myPosition.deltaY(i);
    }

    //Direction -x
    i = -1;
    destination = myPosition.deltaX(i);
    while (board.isPositionOnBoard(destination))
    {
		attackedPosition.push_back(destination);

        if (!board.isPositionFree(destination))
        {
            break;
        }

        --i;
        destination = myPosition.deltaX(i);
    }

    //Direction -y
    i = -1;
    destination = myPosition.deltaY(i);
    while (board.isPositionOnBoard(destination))
    {
		attackedPosition.push_back(destination);

        if (!board.isPositionFree(destination))
        {
            break;
        }

        --i;
        destination = myPosition.deltaY(i);
    }

    return attackedPosition;
}

std::vector<Move> Rook::getPseudoLegalMoves(Board &board)
{
    return Rook::getRookMoves(board, shared_from_this());
}

std::vector<Position> Rook::getAttackedPositions(Board &board)
{
    return Rook::getAttackedPositions(board, shared_from_this());
}
