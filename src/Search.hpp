#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"

class Search
{
public:

	Search(std::shared_ptr<Board> boardPtr);

    int negaMaxRoot(const int depth);
    int negaMaxRootIterativeDeepening(const int timeSec);
    inline int getCurrentScore() {return myEval.evaluate();};
    Move myBestMove;

private:

    std::shared_ptr<Board> myBoard;
    Eval myEval;

    int negaMax(int depth, int alpha, const int beta);
    int evaluate();
};

#endif // SEARCH_H_INCLUDED
