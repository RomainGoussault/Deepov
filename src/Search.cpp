#include "Search.hpp"
#include "Eval.hpp"

int Search::negaMax(int depth, int alpha, int beta)
{
	int score(0);
	int max(-10000);
	MoveGen moveGen(myBoard);

	if (depth == 0)
	{
		return evaluate();
	}

	std::vector<Move> moveList = moveGen.getLegalMoves();
	int nMoves = moveList.size();

	for (int i = 0; i < nMoves; i++)
	{
		Move currentMove = moveList[i];
		myBoard->executeMove(currentMove);
		score = -negaMax(depth - 1, 0, 0);
		if (score > max)
		{
			max = score;
		}
		myBoard->undoMove(currentMove);
	}

	return max;
}

int Search::evaluate()
{
	Eval eval(myBoard); //make Eval static?
	return (-2*myBoard->getColorToPlay() + 1)*eval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}

