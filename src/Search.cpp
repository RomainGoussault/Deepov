#include "Search.hpp"
#include "Eval.hpp"

#include <chrono>
#include <ctime>
#include <ratio>

Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove(), myEval(boardPtr)
{
	myBoard = boardPtr;
}

//Quiescence Search
int Search::qSearch(int alpha, const int beta)
{
	int stand_pat = evaluate();

	if( stand_pat >= beta )
	{
		return beta;
	}
	else if( alpha < stand_pat )
	{
		alpha = stand_pat;
	}

	MoveGen moveGen(myBoard);
	std::vector<Move> moveList = moveGen.generateMoves();
	Eval::sortMoveList(moveList);

	for (auto currentMove : moveList)
	{
		if(currentMove.isCapture())
		{
			int score = 0;
			myBoard->executeMove(currentMove);
			myEval.updateEvalAttributes(currentMove);

			score = -qSearch( -beta, -alpha );

			myBoard->undoMove(currentMove);
			myEval.rewindEvalAttributes(currentMove);

			if( score >= beta )
			{
				return beta;
			}
			else if( score > alpha )
			{
				alpha = score;
			}
		}
	}

	return alpha;
}

int Search::negaMax(const int depth, int alpha, const int beta)
{
	if (depth == 0)
	{
		if(myBoard->getEnemyLastMove()->isCapture())
		{
			return qSearch(alpha, beta);
		}
		else
		{
			return evaluate();
		}
	}

	//check for 1-move repetition
	auto keys = myBoard->getKeysHistory();
	auto currentKey = myBoard->key;
	keys.pop_back();

	if (std::find(keys.begin(), keys.end(), currentKey) != keys.end())
	{
		//Draw
		return Eval::DRAW_SCORE;
	}

	MoveGen moveGen(myBoard);
	std::vector<Move> moveList = moveGen.generateMoves();

	//Check for stalemate or checkmate
	if(moveList.empty())
	{
		if(myBoard->isCheck())
		{
			//checkmate
			return -(Eval::CHECKMATE_SCORE+depth);
		}
		else
		{
			//stalemate
			return Eval::DRAW_SCORE;
		}
	}

	Eval::sortMoveList(moveList);

	for (auto it = moveList.begin(); it != moveList.end(); ++it) {
		Move move = *it;
		if (Move::isSameMove(move, pvTable[currentMaxDepthID-1][currentMaxDepthID-depth])) {
			auto x = *it; // or std::move(*it)
			moveList.erase(it);
			moveList.insert(moveList.begin(), x /* or std::move(x) */);
			break;
		}
	}

	int score = 0;
	for (auto currentMove : moveList)
	{
		//	Move currentMove = moveList[i];
		myBoard->executeMove(currentMove);
		myEval.updateEvalAttributes(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);

		if( score >= beta )
		{
			return beta;   //  fail hard beta-cutoff
		}
		if( score > alpha )
		{
			pvTable[currentMaxDepthID][currentMaxDepthID-depth] = currentMove;
			alpha = score; // alpha acts like max in MiniMax
		}
	}

	return alpha;
}

int Search::negaMaxRoot(const int depth)
{
	int alpha = -999999;
	int beta = -alpha;
	int score = 0;

	MoveGen moveGen(myBoard);

	std::vector<Move> moveList = moveGen.generateMoves();

	for (auto currentMove : moveList)
	{
		myBoard->executeMove(currentMove);
		myEval.updateEvalAttributes(currentMove);

		score = -negaMax(depth - 1, -beta, -alpha);

		if( score > alpha )
		{
			alpha = score;
			myBestMove = currentMove;
		}

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);
	}

	return alpha;
}

int Search::negaMaxRootIterativeDeepening(const int allocatedTimeMS)
{
	int alpha = -999999;
	int beta = -alpha;
	int score = 0;

	//Starting time
	std::chrono::high_resolution_clock::time_point startTime =
			std::chrono::high_resolution_clock::now();

	currentMaxDepthID = 1;
	while(true)
	{
		alpha = -999999;
		beta = -alpha;
		score = 0;

		MoveGen moveGen(myBoard);

		std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
		auto dur = time - startTime;
		int durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

		//check for time
		if(currentMaxDepthID !=1)
		{
			if(durationMS > 0.3*allocatedTimeMS) return alpha; //if there only 2/3 of time left don't go one depth further
		}

		std::vector<Move> moveList = moveGen.generateMoves();

		for (auto it = moveList.begin(); it != moveList.end(); ++it) {
			Move move = *it;
			if (Move::isSameMove(move, pvTable[currentMaxDepthID-1][currentMaxDepthID-currentMaxDepthID])) {
				auto x = *it; // or std::move(*it)
				moveList.erase(it);
				moveList.insert(moveList.begin(), x /* or std::move(x) */);
				break;
			}
		}


		for (auto currentMove : moveList)
		{
			myBoard->executeMove(currentMove);
			myEval.updateEvalAttributes(currentMove);

			score = -negaMax(currentMaxDepthID - 1, -beta, -alpha);

			if( score > alpha )
			{
				alpha = score;
				myBestMove = currentMove;
				pvTable[currentMaxDepthID][0] = myBestMove;

			}
			myBoard->undoMove(currentMove);
			myEval.rewindEvalAttributes(currentMove);
		}

		currentMaxDepthID++;
	}

	return alpha;
}

int Search::evaluate()
{
	return (-2*myBoard->getColorToPlay() + 1)*myEval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}

void Search::printPvTable()
{
	int n = 20;
	while(pvTable[n][0].isNullMove())
	{
		n--;
	}

	for(int i = 1; i<=n; i++)
	{
		std::cout << "currentMaxDepthID: " << i << std::endl;

		for(int j = 0; j<=n; j++)
		{
			std::cout << " " <<i<<j<<pvTable[i][j].toShortString() << "   ";;
		}

		std::cout << std::endl;
		std::cout << std::endl;
	}
}
