#include "Move.hpp"
#include "Piece.hpp"

#include <sstream>
#include <string>

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),
myCapturedPiece(nullptr), myIsCastling(false), myPromotedPiece('\0')
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

PiecePtr Move::getPromotedPiece()
{
    return myPromotedPiece;
}

void Move::setPromotedPiece(PiecePtr piece)
{
    myPromotedPiece = piece ;
}

std::string Move::toShortString() const
{
	std::stringstream ss;
	ss << myOrigin.toShortString() << myDestination.toShortString();

	return ss.str();
}
