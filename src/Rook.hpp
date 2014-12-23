/*
 * Rook.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */
#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"
#include "Board.hpp"

class Rook : public Piece
{
public:

    Rook(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(const Board &board);
    std::vector<Position> getAttackedPositions(const Board &board);
    static std::vector<Move> getRookMoves(const Board &board, PiecePtr piecePtr);
    static std::vector<Position> getAttackedPositions(const Board &board, PiecePtr piecePtr);

    char getChar() const {return 'r';};

};

inline std::ostream& operator<<(std::ostream &strm, const Rook &rook)
{
	strm << "Rook " << static_cast<const Piece &>(rook) << std::endl;
	return strm;
}

#endif /* ROOK_HPP_ */
