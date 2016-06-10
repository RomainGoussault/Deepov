#ifndef MOVEORDERING_H_INCLUDED
#define MOVEORDERING_H_INCLUDED


#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "Move.hpp"


class MoveOrdering
{
public :

    const static int KILLER1_BONUS = 20;
    const static int KILLER2_BONUS = 10;

    inline MoveOrdering() : myKiller1(), myKiller2() {}

    inline Move getKiller1(const unsigned int ply) const {return myKiller1[ply];}
    inline Move getKiller2(const unsigned int ply) const {return myKiller2[ply];}

    void setNewKiller(const Move& move,const unsigned int ply);
    void clearKillers();

    void rateMoves(std::vector<Move>& moveList, const unsigned int ply);
    void rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board, const unsigned int ply, const bool isSee);
    void rateMovesH(std::vector<Move>& moveList, std::shared_ptr<Board> board, const unsigned int ply);

    void sortMoves(std::vector<Move>& moveList);
    std::vector<Move>::iterator getBestCandidate(std::vector<Move>& moveList);



private :
    // TODO : use MAX_DEPTH instead of 64
    Move myKiller1[64];
    Move myKiller2[64];
};

#endif // MOVEORDERING_H_INCLUDED
