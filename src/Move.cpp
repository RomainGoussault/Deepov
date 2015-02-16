#include "Move.hpp"
#include "Piece.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Queen.hpp"

#include <sstream>
#include <string>

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

std::shared_ptr<Piece> Move::getPromotedPawn()
{
        return myPromotedPawn;
}

void Move::setPromotedPiece(char piece)
{
    myPromotedPiece = piece ;
}

void Move::setPromotedPawn(std::shared_ptr<Piece> pawn)
{
    myPromotedPawn = pawn ;
}

std::string Move::toShortString() const
{
	std::stringstream ss;
	ss << myOrigin.toShortString() << myDestination.toShortString();

	return ss.str();
}

//TODO: Rename
std::shared_ptr<Piece> Move::promotePawn(const Position &destination, Board &board)
{
	switch (myPromotedPiece)
	{
	case 'k' :
	{
		PiecePtr promotedPtr(new Knight(destination, board.getTurn()));
		return promotedPtr;
		break;
	}
	case 'b' :
	{
		PiecePtr promotedPtr(new Bishop(destination, board.getTurn()));
		return promotedPtr;
		break;
	}
	case 'r' :
	{
		PiecePtr promotedPtr(new Rook(destination, board.getTurn()));
		return promotedPtr;
		break;
	}
	case 'q' :
	{
		PiecePtr promotedPtr(new Queen(destination, board.getTurn()));
		return promotedPtr;
		break;
	}
	default :
	{
		std::cout << "ERROR IN std::shared_ptr<Piece> Move::promotePawn " << std::endl; //TODO throw exception
		return nullptr;
	}
	}
}
