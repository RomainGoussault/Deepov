#include "Eval.h"

Eval::Eval(FastBoard board) : myBoard(std::make_shared<FastBoard>(board))
{
}

Eval::Eval(std::shared_ptr<FastBoard> boardPtr)
{
    myBoard = boardPtr;
}

int Eval::evaluate()
{
    int score =0;
    return score + 100*getMaterialScore() + getMobilityScore();
}


int Eval::getMobilityScore()
{
    return 1; // Need a way to efficiently get attacking squares
}

int Eval::getMaterialScore()
{
    return 1;
}
