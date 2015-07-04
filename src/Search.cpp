#include "Search.hpp"
#include "Eval.hpp"

#include <chrono>
#include <ctime>
#include <ratio>

Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove(), myEval(boardPtr)
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
        myEval.updateEvalAttributes(currentMove);
		myBoard->executeMove(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

        myEval.rewindEvalAttributes(currentMove);
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

	for (auto currentMove : moveList)
	{
        myEval.updateEvalAttributes(currentMove);
		myBoard->executeMove(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

		if( score > alpha )
		{
			alpha = score;
			myBestMove = currentMove;
		}
        myEval.rewindEvalAttributes(currentMove);
		myBoard->undoMove(currentMove);
	}

	return alpha;
}

int Search::negaMaxRootIterativeDeepening(int allocatedTimeMS)
{
	int alpha = -999999;
	int beta = -alpha;
	int score = 0;

	//Starting time
	std::chrono::high_resolution_clock::time_point startTime =
			std::chrono::high_resolution_clock::now();
	//std::cout << " Romain allocatedTimeMS" << allocatedTimeMS << std::endl;

	int depth = 1;

	while(true)
	{
		alpha = -999999;
		beta = -alpha;
		score = 0;

		MoveGen moveGen(myBoard);

		std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
		auto dur = time - startTime;
	    int durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

		//		std::cout << " Romain duration" << duration.count() << " allocated duration " << allocatedDuration.count() << std::endl;

		//check for time
	    if(depth !=1)
	    {
	    	if(durationMS > 0.3*allocatedTimeMS) return alpha; //if there only 2/3 of time left don't go one depth further
	    }

		std::vector<Move> moveList = moveGen.getMoves();

		for (auto currentMove : moveList)
		{
		    myEval.updateEvalAttributes(currentMove);
			myBoard->executeMove(currentMove);

			score = -negaMax(depth - 1, -beta, -alpha);

			if( score > alpha )
			{
				alpha = score;
				myBestMove = currentMove;
				//std::cout << " Romain myBestMove" << currentMove.toShortString() << std::endl;

			}
            myEval.rewindEvalAttributes(currentMove);
			myBoard->undoMove(currentMove);
		}

		depth++;
		//std::cout << " Romain depth" << depth << std::endl;

	}

	return alpha;
}

int Search::evaluate()
{
	return (-2*myBoard->getColorToPlay() + 1)*myEval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}
