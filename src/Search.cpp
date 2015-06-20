#include "Search.hpp"
#include "Eval.hpp"


#include <chrono>
#include <ctime>
#include <ratio>

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

int Search::negaMaxRootIterativeDeepening(int allocatedTimeSec)
{
	//TODO allocatedTimeSec should be in ms
	int alpha = -999999;
	int beta = -alpha;
	int score = 0;

	//Starting time
	std::chrono::high_resolution_clock::time_point startTime =
			std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> allocatedDuration(allocatedTimeSec);

	int depth = 1;

	while(true)
	{
		alpha = -999999;
		beta = -alpha;
		score = 0;

		MoveGen moveGen(myBoard);

		std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = std::chrono::duration_cast<std::chrono::duration<float>>(time - startTime);

		//		std::cout << " Romain duration" << duration.count() << " allocated duration " << allocatedDuration.count() << std::endl;

		//check for time
		if(duration > allocatedDuration) return alpha; //if there only 1/3 of time left don't go one depth further


		std::vector<Move> moveList = moveGen.getMoves();
		//int nMoves = moveList.size();

		for (auto currentMove : moveList)
		{
			myBoard->executeMove(currentMove);

			score = -negaMax(depth - 1, -beta, -alpha);

			if( score > alpha )
			{
				alpha = score;
				myBestMove = currentMove;
				std::cout << " Romain myBestMove" << currentMove.toShortString() << std::endl;

			}

			myBoard->undoMove(currentMove);
		}

		depth++;
		//	std::cout << " Romain depth" << depth << std::endl;

	}

	return alpha;
}

int Search::evaluate()
{
	Eval eval(myBoard); //make Eval static?
	return (-2*myBoard->getColorToPlay() + 1)*eval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}

