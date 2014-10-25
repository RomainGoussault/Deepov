/*
 * Knight.hpp
 *
 */
#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Knight : public Piece
{
public:

    Knight(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
    static std::vector<Move> getKnightMoves(Board &board, PiecePtr piecePtr);

    char getChar() const {return 'n';};
};

inline std::ostream& operator<<(std::ostream &strm, const Knight &Knight)
{
	strm << "Knight " << static_cast<const Piece &>(Knight) << std::endl;
	return strm;
}

#endif /* KNIGHT_HPP_ */

