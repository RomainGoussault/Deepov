/*
 * Queen.hpp
 
 */
#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Queen : public Piece
{
public:

    Queen(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);
    char getChar() const {return 'q';};
};

inline std::ostream& operator<<(std::ostream &strm, const Queen &rook)
{
	strm << "Queen " << static_cast<const Piece &>(rook) << std::endl;
	return strm;
}

#endif /* QUEEN_HPP_ */
