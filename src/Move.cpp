#include "Move.hpp"
#include "Piece.hpp"

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination), myIsPromotion(false)
{
}

void Move::setCapturedPiece(Piece &piece)
{
    myCapturedPiece.reset(&piece);
}

Piece Move::getCapturedPiece()
{
    return *myCapturedPiece;
}
