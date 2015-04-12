#include "Move.hpp"
#include "Piece.hpp"

#include <sstream>
#include <string>

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),
myCapturedPiece(nullptr), myPromotedPiece(nullptr), myPromotedPawn(nullptr), myIsCastling(false), myCancelledCastling{false,false}
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

bool Move::isPromotion() const
{
	return myPromotedPiece != nullptr;
}

void Move::setIsCastling()
{
    myIsCastling = true;
}

bool Move::isCastling() const
{
	return myIsCastling;
}

bool Move::getCancelledCastling(const int &side) const
{
    if (side == 0)
    {
        return myCancelledCastling[0];
    }
    else
    {
        return myCancelledCastling[1];
    }
    /* Same here, do i add this ? */
//    else
//    {
//        throw std::runtime_error("setCancelledCastling out of bound" );
//    }
}

void Move::setCancelledCastling(const int &side)
{
    if (side == 0)
    {
        myCancelledCastling[0]=true;
    }
    else if (side == 1)
    {
        myCancelledCastling[1]=true;
    }
    /* Do i add this ? */
//    else
//    {
//        throw std::runtime_error("setCancelledCastling out of bound" );
//    }
}

PiecePtr Move::getPromotedPiece()
{
    return myPromotedPiece;
}

void Move::setPromotedPiece(PiecePtr piece)
{
    myPromotedPiece = piece ;
}

PiecePtr Move::getPromotedPawn()
{
    return myPromotedPawn;
}

void Move::setPromotedPawn(PiecePtr pawn)
{
    myPromotedPawn = pawn ;
}

std::string Move::toShortString() const
{
	std::stringstream ss;
	ss << myOrigin.toShortString() << myDestination.toShortString();

	return ss.str();
}
