#include "Search.h"

int Search::negaMax(int depth, int alpha, int beta)
{
    int score(0);
    int max(-10000);
    MoveGen moves(myBoard);

    if (depth == 0)
    {
        return (-2*myBoard->getColorToPlay() + 1)*1; //evaluate(); /* returns +evaluate for WHITE, -evaluate for BLACK */
    }

		std::vector<FastMove> moveList = moves.getLegalMoves();
		int nMoves = moveList.size();

		for (int i = 0; i < nMoves; i++)
		{
			FastMove currentMove = moveList[i];
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
