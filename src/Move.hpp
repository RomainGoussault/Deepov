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
#include "Board.hpp"
#include "Piece.hpp"


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
	std::shared_ptr<Piece> getPromotedPawn();

	std::string toShortString() const;


	//ALL SETS
	void setCapturedPiece(std::shared_ptr<Piece> piece);
	void setIsPromotion();
	void setIsCastling();
	void setPromotedPiece(char piece);
	void setPromotedPawn(std::shared_ptr<Piece> pawn);

    // Construction of a new promoted piece
    PiecePtr promotePawn(const Position &destination, Board &board);

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
	strm << "Orig: " << move.getOrigin() << "  Dest: " << move.getDestination();
	return strm;
}

#endif /* MOVE_HPP_ */
