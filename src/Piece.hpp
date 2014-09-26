/*
 * Piece.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef Piece_HPP_
#define Piece_HPP_

#include <ostream>

#include "Position.hpp"
#include "Color.hpp"

class Piece
{
public:

	static const char ROOK = 1;
	Piece(char value, Position position, Color::value color, bool isPinned);
	Piece(char value, Position position, Color::value color);
	Piece(char value, Position position);
	Piece();
	Position getPosition();
	char getValue() const;
	bool isNull();

private:

	char myValue;
	Position myPosition;
	Color::value myColor;
	bool myIsPinned;
};

inline std::ostream& operator<<(std::ostream &strm, const Piece &piece)
{
	std::string name;

	switch (piece.getValue())
	{
	case Piece::ROOK:
		name = "Rook";
		break;

	default:
		name = "Unknown Piece";
	}

	strm << "Piece value:" << name;
	return strm;
}

#endif /* Piece_HPP_ */
