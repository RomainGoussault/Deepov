/*
 * Pawn.hpp
 */

#include "Pawn.hpp"
#include "Board.hpp"

Pawn::Pawn(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Pawn::getPawnMoves(Board &board, PiecePtr piecePtr)
{
    std::vector<Move> PawnMoves;
    PiecePtr otherPiece;
    Position myPosition = piecePtr->getPosition();

    return PawnMoves;
}

std::vector<Move> Pawn::getPseudoLegalMoves(Board &board)
{
    return Pawn::getPawnMoves(board, shared_from_this());
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

