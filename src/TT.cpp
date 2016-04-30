#include "TT.hpp"

TT globalTT = TT();

void TT::setTTEntry(Zkey zkey, int depth, int score, NodeType node, Move bestMove)
{
    U64 index = zkey % TT_SIZE;
    TTEntry newEntry(zkey, depth, score, node, bestMove);

    // Replace if node closer to root (ie. greater evaluation depth)
    if (depth > myTTable[index].getDepth())
    {
        myTTable[index] = newEntry ;
    }
}


TTEntry* TT::probeTT(Zkey zkey, int depth)
{
    U64 index = zkey % TT_SIZE;
    // We have a match 
    if (myTTable[index].getZkey() == zkey && myTTable[index].getNodeType() != NodeType::NONE && myTTable[index].getDepth() >= depth)
    {
        return &myTTable[index];
    }
    // If key is not matched, or depth lower, return empty pointer as we want to continue the search
    else
    {
        return nullptr;
    }
}
