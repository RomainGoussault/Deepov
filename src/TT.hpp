#ifndef TT_HPP_
#define TT_HPP_

#include "Move.hpp"
#include "Types.hpp"
#include "TTEntry.hpp"

class TT {

public:

    const static int TT_SIZE = 1048576;

	TT()
    {
    }

    void setTTEntry(Zkey zkey, int depth, int score, NodeType node, Move bestMove);
    TTEntry* probeTT(Zkey zkey, int depth);

private:
    TTEntry myTTable[TT_SIZE];


};

#endif /* TT_HPP_ */
