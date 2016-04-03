#include "TT.hpp"


void TT::setTTEntry(Zkey zkey, int depth, int score, NodeType node, Move bestMove)
{
    unsigned long int index = zkey % TT_SIZE;
    TTEntry newEntry(zkey, depth, score, node, bestMove);

    // Always replace strategy
    myTTable[index] = newEntry ;
    
    // TODO: check for depth
}


TTEntry* TT::probeTT(Zkey zkey, int depth)
{
    unsigned long int index = zkey % TT_SIZE;
    // If key is not matched, return empty pointer
    if (myTTable[index].getNodeType() == NodeType::NONE)
    {
        return nullptr;
    }

    // We have a match 
    else if (myTTable[index].getDepth() >= depth)   // Check we have already explored at a better depth 
    {
        return &myTTable[index];
    }
    else
    {
        return &myTTable[index];
    }
}
