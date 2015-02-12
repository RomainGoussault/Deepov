#include "Move.hpp"
#include "Piece.hpp"
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

PiecePtr Move::promotePawn(Position destination, Board board)
{
    switch (myPromotedPiece)
        {
        init_label:
        case 'k' :
        {
            PiecePtr promotedPtr(new Knight(destination, board.getTurn()));
            return promotedPtr;
            break;
        }
        case 'b' :
        {
            PiecePtr promotedPtr(new Bishop(destination, board.getTurn())));
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
            std::shared_ptr<Piece> promotedPtr(new Queen(destination, board.getTurn()));
            return promotedPtr;
            break;
        }
        default :
        {
            // asks the user to chose a valid letter and go back to switch start
            char promotedPiece;
            std::cout << "Choose promotion piece : k, b, r or q. " << std::endl;
            std::cin >> promotedPiece;

            while (promotedPiece != 'k' && promotedPiece != 'b' && promotedPiece != 'r' && promotedPiece != 'q')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<streamsize>::max());
                std::cout << "Choose a correct promotion piece : k, b, r or q. " << std::endl;
                std::cin >> promotedPiece;
            }
            goto init_label;
        }
    }
}

