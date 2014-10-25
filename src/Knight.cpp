/*
 * Knight.hpp
 *
 */

#include "Knight.hpp"
#include "Board.hpp"

Knight::Knight(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Knight::getKnightMoves(Board &board, PiecePtr piecePtr)
{
    std::vector<Move> KnightMoves;
    PiecePtr otherPiece;
    Position myPosition = piecePtr->getPosition();

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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
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
            if (piecePtr->areColorDifferent(*otherPiece))
            {
                possibleMove.setCapturedPiece(otherPiece);
                KnightMoves.push_back(possibleMove);
            }
        }
    }


    return KnightMoves;
}

std::vector<Move> Knight::getPseudoLegalMoves(Board &board)
{
    return Knight::getKnightMoves(board, shared_from_this());
}

