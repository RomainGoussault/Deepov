/*
 * Pawn.hpp
 */

#include "Pawn.hpp"
#include "Board.hpp"

Pawn::Pawn(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Pawn::getPseudoLegalMoves(Board &board)
{
    std::vector<Move> pawnMoves;
    PiecePtr otherPiece;
    int direction = getDirection();

   if (isOnStartingRank())
   {
       if (board.isPositionFree(myPosition.deltaY(direction)) && board.isPositionFree(myPosition.deltaY(2*direction)))
       {
            Position destination = myPosition.deltaY(2*direction);
            Move possibleMove(myPosition,destination);
            pawnMoves.push_back(possibleMove);
       }
   }

/*   else if
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
            otherPiece = board.getPiecePtr(destination);
            // look for capture
            if (piecePtr->areColorDifferent(*otherPiece))
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
*/

    return pawnMoves;
}


int Pawn::getDirection() const {
    if (myColor == WHITE) {
        return 1;
    }
    else {
        return -1;
    }
}

bool Pawn::isOnGoodRankForEnPassant() const {
    if (myColor == WHITE) {
        return (myPosition.getY() == 4);
    }
    else {
        return (myPosition.getY() == 3);
    }
}

bool Pawn::isEnPassantPossible(Board &board) const {
    if (!isOnGoodRankForEnPassant()) {
        return false;
    }
    else {
        return false; // Need to add getLastMove in Board class
    }
}

bool Pawn::isOnStartingRank() const {
    if (myColor == WHITE) {
        return (myPosition.getY() == 1);
    }
    else {
        return (myPosition.getY() == 6);
    }
}

bool Pawn::isOnLastRank() const {
    if (myColor == WHITE) {
        return (myPosition.getY() == 7);
    }
    else {
        return (myPosition.getY() == 0);
    }
}

bool Pawn::isGoingToPromote() const{
    if (myColor == WHITE) {
        return (myPosition.getY() == 6);
    }
    else {
        return (myPosition.getY() == 1);
    }
}

