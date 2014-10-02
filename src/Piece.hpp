/*
 * Piece.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef Piece_HPP_
#define Piece_HPP_

#include <ostream>
#include <vector>

#include "Position.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Board;

class Piece
{
public:

	Piece(Position position, Color::value color, bool isPinned);
	Piece(Position position, Color::value color);
	Piece(Position position);
	Piece();
	Position getPosition();
	char getValue() const;
	bool isEmpty();
	std::vector<Move> getPseudoLegalMoves(Board &board);

protected:

	Position myPosition;

private:

	bool myIsEmpty;
	Color::value myColor;
	bool myIsPinned;
};

#endif /* Piece_HPP_ */
