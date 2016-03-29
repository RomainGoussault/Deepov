#ifndef MOVEORDERING_H_INCLUDED
#define MOVEORDERING_H_INCLUDED


#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "Move.hpp"


class MoveOrdering
{
public :

    MoveOrdering() : myKiller1(), myKiller2() {};
    MoveOrdering(Move killer1, Move killer2) : myKiller1(killer1), myKiller2(killer2) {};

    void rateMoves(std::vector<Move>& moveList);
    void rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board);

    void sortMoves(std::vector<Move>& moveList);
    std::vector<Move>::iterator getBestCandidate(std::vector<Move>& moveList);

private :
    Move myKiller1;
    Move myKiller2;
};

#endif // MOVEORDERING_H_INCLUDED
