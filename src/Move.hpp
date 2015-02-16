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
	std::shared_ptr<Piece> getCapturedPiece();
	std::shared_ptr<Piece> getPromotedPiece();

	std::string toShortString() const;

	//ALL SETS
	void setCapturedPiece(std::shared_ptr<Piece> piece);
	void setIsCastling();
	void setPromotedPiece(std::shared_ptr<Piece> piece);

private:

	Position myOrigin;
	Position myDestination;

	std::shared_ptr<Piece> myCapturedPiece;

	bool myIsCastling;
	std::shared_ptr<Piece> myPromotedPiece;

};

inline std::ostream& operator<<(std::ostream &strm, const Move &move)
{
	strm << "Orig: " << move.getOrigin() << "  Dest: " << move.getDestination();
	return strm;
}

#endif /* MOVE_HPP_ */
