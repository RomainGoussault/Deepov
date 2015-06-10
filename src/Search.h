#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include "FastBoard.hpp"
#include "MoveGen.hpp"

class Search
{
public:
    int negaMax(int depth, int alpha, int beta);
private:
    std::shared_ptr<FastBoard> myBoard;

};


#endif // SEARCH_H_INCLUDED
