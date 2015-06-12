#include "Search.hpp"
#include "Eval.hpp"

Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove()
{
    myBoard = boardPtr;
}

int Search::negaMax(int depth, int alpha, int beta)
{
	int score = 0;
	int max = -10000;

	MoveGen moveGen(myBoard);

	if (depth == 0)
	{
		return evaluate();
	}

	std::vector<Move> moveList = moveGen.getMoves();
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

int Search::negaMaxRoot(int depth, int alpha, int beta)
{
	int score = 0;
	int max = -10000;

	MoveGen moveGen(myBoard);

	std::vector<Move> moveList = moveGen.getMoves();
	int nMoves = moveList.size();
	std::cout << "nMoves " << nMoves << std::endl;

	for (int i = 0; i < nMoves; i++)
	{
		Move currentMove = moveList[i];
		myBoard->executeMove(currentMove);
		score = -negaMax(depth - 1, 0, 0);
			std::cout << "Move  " << currentMove.toShortString() << "   score " << score << std::endl;
		if (score > max)
		{
			max = score;
			myBestMove = currentMove;
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

