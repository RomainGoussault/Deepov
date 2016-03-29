#ifndef MOVEORDERING_H_INCLUDED
#define MOVEORDERING_H_INCLUDED


#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "Move.hpp"


class MoveOrdering
{
public :

    inline MoveOrdering() : myKiller1(), myKiller2() {}

    inline Move getKiller1(const int ply) const {return myKiller1[ply];}
    inline Move getKiller2(const int ply) const {return myKiller2[ply];}


    void setNewKiller(const Move& move,const unsigned int ply);

    void rateMoves(std::vector<Move>& moveList);
    void rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board);

    void sortMoves(std::vector<Move>& moveList);
    std::vector<Move>::iterator getBestCandidate(std::vector<Move>& moveList);



private :
    std::vector<Move> myKiller1;
    std::vector<Move> myKiller2;
};

#endif // MOVEORDERING_H_INCLUDED
