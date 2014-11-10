/*
 * Knight.hpp
 *
 */

#include "Knight.hpp"


Knight::Knight(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Knight::getPseudoLegalMoves(Board &board)
{
    std::vector<Move> KnightMoves;
    PiecePtr otherPiece;

    // Direction +2x +y

    Position destination = myPosition.deltaX(2);
    destination = destination.deltaY(1);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction +x +2y

    destination = myPosition.deltaX(1);
    destination = destination.deltaY(2);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction -x +2y

    destination = myPosition.deltaX(-1);
    destination = destination.deltaY(2);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction -2x +y

    destination = myPosition.deltaX(-2);
    destination = destination.deltaY(1);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction -2x -y

    destination = myPosition.deltaX(-2);
    destination = destination.deltaY(-1);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction -x -2y

    destination = myPosition.deltaX(-1);
    destination = destination.deltaY(-2);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction +x -2y

    destination = myPosition.deltaX(1);
    destination = destination.deltaY(-2);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }

    // Direction +2x -y

    destination = myPosition.deltaX(2);
    destination = destination.deltaY(-1);
    if (board.isPositionOnBoard(destination))
    {
        Move possibleMove(myPosition, destination);

        if (board.isPositionFree(destination))
        {
            KnightMoves.push_back(possibleMove);
        }
        else
        {
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }


    return KnightMoves;
}
