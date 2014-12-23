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
#include <boost/optional.hpp>
#include "Board.hpp"
#include <cmath>

class Pawn : public Piece
{
public:

    Pawn(Position position, int color);

    std::vector<Move> getPseudoLegalMoves(const Board &board);
    std::vector<Position> getAttackedPositions(const Board &board);

    /***************************** Promotion functions *********************************/
    std::vector<Move> getPromotionMoves(Position const& destination);
    bool isGoingToPromote() const;

    /***************************** EnPassant functions *********************************/

    bool isOnGoodRankForEnPassant() const;
    bool isEnPassantPossible(const Board &board) const;
    bool isEnPassantPossibleFEN(const Board &board) const;

    /******************************* Other functions ***********************************/

    int getDirection() const;
    bool isOnStartingRank() const;
    bool isOnLastRank() const;

    char getChar() const {return 'p';};
};

inline std::ostream& operator<<(std::ostream &strm, const Pawn &Pawn)
{
	strm << "Pawn " << static_cast<const Piece &>(Pawn) << std::endl;
	return strm;
}

#endif /* PAWN_HPP_ */


