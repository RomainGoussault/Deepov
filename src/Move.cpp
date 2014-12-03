#include "Move.hpp"
#include "Piece.hpp"

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),
myCapturedPiece(nullptr), myIsPromotion(false), myIsCastling(false), myPromotedPiece('\0'), myPromotedPawn(nullptr)
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

void Move::setIsCastling()
{
    myIsCastling = true;
}

char Move::getPromotedPiece()
{
    return myPromotedPiece;
}


void Move::setPromotedPiece(char piece)
{
    myPromotedPiece = piece ;
}

void Move::setPromotedPawn(std::shared_ptr<Piece> pawn)
{
    myPromotedPawn = pawn ;
}
