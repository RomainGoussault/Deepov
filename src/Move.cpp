#include "Move.hpp"
#include "Piece.hpp"

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),  myCapturedPiece(nullptr), myIsPromotion(false)
{
}

void Move::setCapturedPiece(PiecePtr piece)
{
    myCapturedPiece = piece;
}

Piece Move::getCapturedPiece()
{
    return *myCapturedPiece;
}

Position Move::getOrigin() const
{
    return myOrigin;
}
Position Move::getDestination() const
{
    return myDestination;
}
