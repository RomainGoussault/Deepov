#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "Board.hpp"
#include "MoveGen.hpp"

class Search
{
public:

	Search(std::shared_ptr<Board> boardPtr);

    int negaMaxRoot(int depth);
    int negaMaxRoot(int depth, int time);
    Move myBestMove;

private:

    std::shared_ptr<Board> myBoard;

    int negaMax(int depth, int alpha, int beta);
    int evaluate();
};


#endif // SEARCH_H_INCLUDED
