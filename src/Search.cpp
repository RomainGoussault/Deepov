#include "Search.hpp"
#include "Eval.hpp"

Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove()
{
	myBoard = boardPtr;
}

int Search::negaMax(int depth, int alpha, int beta)
{
	int score = 0;

	MoveGen moveGen(myBoard);

	if (depth == 0)
	{
		return evaluate();
	}

	std::vector<Move> moveList = moveGen.getMoves();
//	int nMoves = moveList.size();

	for (auto currentMove : moveList)
	{
	//	Move currentMove = moveList[i];
		myBoard->executeMove(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

		myBoard->undoMove(currentMove);

		if( score >= beta )
		{
			return beta;   //  fail hard beta-cutoff
		}
		if( score > alpha )
		{
			alpha = score; // alpha acts like max in MiniMax
		}
	}

	return alpha;
}

int Search::negaMaxRoot(int depth)
{
	int alpha = -999999;
	int beta = -alpha;
	int score = 0;

	MoveGen moveGen(myBoard);

	std::vector<Move> moveList = moveGen.getMoves();
	//int nMoves = moveList.size();

	for (auto currentMove : moveList)
	{
		//Move currentMove = moveList[i];
		myBoard->executeMove(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

		if( score > alpha )
		{
			alpha = score;
			myBestMove = currentMove;
		}

		myBoard->undoMove(currentMove);
	}

	return alpha;
}

int Search::evaluate()
{
	Eval eval(myBoard); //make Eval static?
	return (-2*myBoard->getColorToPlay() + 1)*eval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}

