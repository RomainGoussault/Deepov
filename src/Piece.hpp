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
#include <memory>

#include "Position.hpp"
#include "Color.hpp"
#include "Move.hpp"
class Board;

typedef std::shared_ptr<Piece> PiecePtr;


class Piece
{
public:


	Piece();
	Piece(Position position);
	Piece(Position position, int color);
	Piece(Position position, int color, bool isPinned);

	//virtual destructor
	virtual ~Piece()
	{
	}

    void setPosition(Position position);
	Position getPosition() const;
	char getValue() const;
	int getColor() const;
	bool areColorDifferent(Piece &piece);
	virtual std::vector<Move> getPseudoLegalMoves(Board &board) = 0;
	virtual char getChar() const = 0;

protected:

	Position myPosition;

private:

	int myColor;
	bool myIsPinned;
};

inline std::ostream& operator<<(std::ostream &strm, const Piece &piece)
{
    std::string color = piece.getColor() == 0 ? " WHITE" : " BLACK";

   	strm << piece.getPosition() << color <<std::endl;
	return strm;
}

#endif /* Piece_HPP_ */
