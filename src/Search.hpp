#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "Board.hpp"
#include "MoveGen.hpp"

class Search
{
public:
    int negaMax(int depth, int alpha, int beta);
    int evaluate();
private:
    std::shared_ptr<Board> myBoard;

};


#endif // SEARCH_H_INCLUDED
