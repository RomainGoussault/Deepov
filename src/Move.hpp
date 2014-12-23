/*
 * Move.hpp
 *
 *  Created on: 26 sept. 2014
 *      Author: Romain
 */

#ifndef MOVE_HPP_
#define MOVE_HPP_

#include <memory>
#include "Position.hpp"


class Piece;

class Move
{
public:

	Move(Position origin, Position destination);
	//myCapturedPiece needs to be a pointer
	// because the Piece is a forward declaration

	// ALL GETS
	Position getOrigin() const;
	Position getDestination() const;
	bool isPromotion() const;
	bool isCastling() const;
	std::shared_ptr<Piece> getCapturedPiece();
	char getPromotedPiece();

	//ALL SETS
	void setCapturedPiece(std::shared_ptr<Piece> piece);
	void setIsPromotion();
	void setIsCastling();
	void setPromotedPiece(char piece);
	void setPromotedPawn(std::shared_ptr<Piece> pawn);

private:

    Position myOrigin;
    Position myDestination;
    std::shared_ptr<Piece> myCapturedPiece;

    // For promotion moves, initialized to false
    bool myIsPromotion;
    bool myIsCastling;
    char myPromotedPiece; // This is a character corresponding to the piece type
    // Interpretation to be done in executeMove; so i don't have to carry more objects
    std::shared_ptr<Piece> myPromotedPawn;


};

inline std::ostream& operator<<(std::ostream &strm, const Move &move)
{
    strm << "Orig: "  << move.getOrigin()  << "  Dest: "  << move.getDestination()<< std::endl;
    return strm;
}

#endif /* MOVE_HPP_ */
