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

class Board;
class Piece;

class Move
{
public:

	Move(Position origin, Position destination);

	// ALL GETS
	Position getOrigin() const;
	Position getDestination() const;
	bool isPromotion() const;
	bool isCastling() const;
	bool getCancelledCastling(const int &side) const;
	std::shared_ptr<Piece> getCapturedPiece();
	std::shared_ptr<Piece> getPromotedPiece();
	std::shared_ptr<Piece> getPromotedPawn();

	std::string toShortString() const;

	//ALL SETS
	void setCapturedPiece(std::shared_ptr<Piece> piece);
	void setIsCastling();
	void setCancelledCastling(const int &side);
	void setPromotedPiece(std::shared_ptr<Piece> piece);
	void setPromotedPawn(std::shared_ptr<Piece> pawn);

private:

	Position myOrigin;
	Position myDestination;
	std::shared_ptr<Piece> myCapturedPiece;
    std::shared_ptr<Piece> myPromotedPiece;
    std::shared_ptr<Piece> myPromotedPawn;
	bool myIsCastling;
	bool myCancelledCastling[2]; /* tab[0] for king side, tab[1] for queen side */

};

inline std::ostream& operator<<(std::ostream &strm, const Move &move)
{
	strm << "Orig: " << move.getOrigin() << "  Dest: " << move.getDestination();
	return strm;
}

#endif /* MOVE_HPP_ */
