#ifndef MOVEORDERING_H_INCLUDED
#define MOVEORDERING_H_INCLUDED


#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "Move.hpp"


namespace MoveOrdering
{
    void rateMoves(std::vector<Move>& moveList);
    void rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board);

    void sortMoves(std::vector<Move>& moveList);
    std::vector<Move>::iterator getBestCandidate(std::vector<Move>& moveList);
};

#endif // MOVEORDERING_H_INCLUDED
