#include "Move.hpp"
#include "Piece.hpp"

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),  myCapturedPiece(nullptr), myIsPromotion(false), myPromotedPiece(nullptr)
{
}

void Move::setCapturedPiece(PiecePtr piece)
{
    myCapturedPiece = piece;
}

PiecePtr Move::getCapturedPiece()
{
    return myCapturedPiece;
}

Position Move::getOrigin() const
{
    return myOrigin;
}
Position Move::getDestination() const
{
    return myDestination;
}

void Move::setIsPromotion()
{
    myIsPromotion = true;
}

std::shared_ptr<Piece> Move::getPromotedPiece()
{
    return myPromotedPiece;
}


void Move::setPromotedPiece(PiecePtr piece)
{
    myPromotedPiece = piece ;
}
