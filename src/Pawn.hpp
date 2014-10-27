/*
 * Pawn.hpp
 *
 */
#ifndef PAWN_HPP_
#define PAWN_HPP_

#include "Position.hpp"
#include "Piece.hpp"
#include "Color.hpp"
#include "Move.hpp"

class Pawn : public Piece
{
public:

    Pawn(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(Board &board);

    int getDirection() const;
    bool isOnGoodRankForEnPassant() const;
    bool isEnPassantPossible(Board &board) const;
    bool isOnStartingRank() const;
    bool isOnLastRank() const;
    bool isGoingToPromote() const;

    char getChar() const {return 'p';};
};

inline std::ostream& operator<<(std::ostream &strm, const Pawn &Pawn)
{
	strm << "Pawn " << static_cast<const Piece &>(Pawn) << std::endl;
	return strm;
}

#endif /* PAWN_HPP_ */


