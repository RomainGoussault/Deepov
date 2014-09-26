/*
 * Board.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <array>

#include "Piece.hpp"
#include "Position.hpp"

class Board
{
public:

	static const int BOARD_SIZE = 7;

	void addPiece(Piece piece, Position position);
	void addPiece(Piece piece);

	Board();

private:

	std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> myPieces;
};


#endif /* BOARD_HPP_ */
