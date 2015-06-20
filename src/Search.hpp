#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"

class Search
{
public:

	Search(std::shared_ptr<Board> boardPtr);

    int negaMaxRoot(int depth);
    int negaMaxRootIterativeDeepening(int timeSec);
    Move myBestMove;

private:

    std::shared_ptr<Board> myBoard;
    Eval myEval;

    int negaMax(int depth, int alpha, int beta);
    int evaluate();
};


#endif // SEARCH_H_INCLUDED
