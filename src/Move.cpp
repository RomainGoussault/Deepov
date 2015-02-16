#include "Move.hpp"
#include "Piece.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"

#include <sstream>
#include <string>

Move::Move(Position origin, Position destination) : myOrigin(origin), myDestination(destination),
myCapturedPiece(nullptr), myIsPromotion(false), myIsCastling(false), myPromotedPiece('\0')
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

bool Move::isPromotion() const
{
	return myIsPromotion;
}

void Move::setIsCastling()
{
    myIsCastling = true;
}

bool Move::isCastling() const
{
	return myIsCastling;
}

char Move::getPromotedPiece()
{
    return myPromotedPiece;
}

void Move::setPromotedPiece(char piece)
{
    myPromotedPiece = piece ;
}

std::string Move::toShortString() const
{
	std::stringstream ss;
	ss << myOrigin.toShortString() << myDestination.toShortString();

	return ss.str();
}

//TODO: Rename
PiecePtr Move::promotePawn(int pieceColor)
{
	switch (myPromotedPiece)
	{
	case 'k' :
	{
		PiecePtr promotedPtr(new Knight(myDestination, pieceColor));
		return promotedPtr;
	}
	case 'b' :
	{
		PiecePtr promotedPtr(new Bishop(myDestination, pieceColor));
		return promotedPtr;
	}
	case 'r' :
	{
		PiecePtr promotedPtr(new Rook(myDestination, pieceColor));
		return promotedPtr;
	}
	case 'q' :
	{
		PiecePtr promotedPtr(new Queen(myDestination, pieceColor));
		return promotedPtr;
	}
	default :
	{
		std::cout << "ERROR IN std::shared_ptr<Piece> Move::promotePawn " << std::endl; //TODO throw exception
		return nullptr;
	}
	}
}
