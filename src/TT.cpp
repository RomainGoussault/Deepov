#include "TT.hpp"

TT globalTT = TT();

void TT::setTTEntry(Zkey zkey, int depth, int score, NodeType node, Move16 bestMove, int moveCounter)
{
    U64 index = zkey % TT_SIZE;

    // Replace if node closer to root (ie. greater evaluation depth)
    if (TTEntry::K * depth + moveCounter >= myTTable[index].getTTValue())
    {
        TTEntry newEntry(zkey, depth, score, node, bestMove, moveCounter);
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
