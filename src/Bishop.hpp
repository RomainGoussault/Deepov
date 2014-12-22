/*
 * Bishop.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"
#include "Board.hpp"

class Bishop : public Piece
{
public:

    Bishop(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
    static std::vector<Move> getBishopMoves(Board &board, PiecePtr piecePtr);
    std::vector<Position> getAttackedPositions(Board &board){return std::vector<Position>();};
    static std::vector<Position> getAttackedPositions(Board &board, PiecePtr piecePtr);

    char getChar() const {return 'b';};
};

inline std::ostream& operator<<(std::ostream &strm, const Bishop &bishop)
{
	strm << "Bishop " << static_cast<const Piece &>(bishop) << std::endl;
	return strm;
}

#endif /* BISHOP_HPP_ */
