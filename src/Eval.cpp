#include "Eval.h"

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
