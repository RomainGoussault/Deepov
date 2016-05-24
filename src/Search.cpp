#include "Search.hpp"
#include "Eval.hpp"
#include "TT.hpp"

#include <chrono>
#include <ctime>
#include <ratio>
#include <algorithm>


Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove(),myMovesSearched(0), myEval(boardPtr),myMoveOrder(),myPly(0)
{
	myBoard = boardPtr;
}

void Search::clearSearchData()
{
    // Clear the killer when starting a new search
    myMoveOrder.clearKillers();
    // Clear other things (TODO)

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

	myMoveOrder.rateMoves(moveList, myBoard, myPly, false);
	myMoveOrder.sortMoves(moveList);

	for (auto currentMove : moveList)
	{
		//Continue only for capture moves with SEE > 0
		if(currentMove.isCapture() && myBoard->seeCapture(currentMove, Utils::getOppositeColor(myBoard->getColorToPlay())) > 0)
		{
			int score = 0;
			myBoard->executeMove(currentMove);
			myEval.updateEvalAttributes(currentMove);
			myPly++;

			score = -qSearch( -beta, -alpha );

			myBoard->undoMove(currentMove);
			myEval.rewindEvalAttributes(currentMove);
			myPly--;

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
	int alpha_old = alpha;

	if (depth <= 0) // If we call negaMaxRoot at depth = 0 , depth =-1
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

	auto ttEntry = globalTT.probeTT(currentKey, depth); // returns non nullpr if key exists and depth is greater
	if(ttEntry) // we have a match in the transposition table with a greater depth
	{
        // If info in the entry is valuable, use it
        if (ttEntry->getNodeType() == NodeType::EXACT)
        {
            return ttEntry->getScore();
        }
        else if (ttEntry->getNodeType() == NodeType::UPPER && ttEntry->getScore() <= alpha)
        {
            return alpha;
        }
        else if (ttEntry->getNodeType() == NodeType::LOWER && ttEntry->getScore() >= beta)
        {
            return beta;
        }
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

	bool isSEE = false;
	myMoveOrder.rateMoves(moveList, myBoard, myPly, isSEE);
	myMoveOrder.sortMoves(moveList);

	int score = 0;
    Move bestMove = Move();
    int bestScore = -999999;

	for (auto currentMove : moveList)
	{
		myBoard->executeMove(currentMove);
		myEval.updateEvalAttributes(currentMove);
		myPly++;

		score = -negaMax(depth - 1, -beta, -alpha);

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);   
		myPly--;

		if(score >= beta)
		{
			//update killer and TT
			myMoveOrder.setNewKiller(currentMove,myPly);
			globalTT.setTTEntry(currentKey, depth, score, NodeType::LOWER, currentMove.getMove16(), myBoard->myHalfMovesCounter);
			return beta;   //  fail hard beta-cutoff
		}

        if (score > bestScore) 
        {
            bestScore = score ;
            bestMove = currentMove ;
		    if( score > alpha )
		    {
			    alpha = score; // alpha acts like max in MiniMax
		    }
        }
	}

	  // store hash info
	  if (alpha > alpha_old)
			globalTT.setTTEntry(currentKey, depth, bestScore, NodeType::EXACT, bestMove.getMove16(), myBoard->myHalfMovesCounter);
	  else
			globalTT.setTTEntry(currentKey, depth, alpha, NodeType::UPPER, bestMove.getMove16(), myBoard->myHalfMovesCounter);


	return alpha;
}

int Search::negaMaxRoot(const int depth)
{
    clearSearchData();

	int alpha = -999999;
	int beta = -alpha;
	int score = 0;
	myMovesSearched = 0;
	myPly=1;

	auto currentKey = myBoard->key;
	auto ttEntry = globalTT.probeTT(currentKey, depth); // returns non nullpr if key exists and depth is greater
	if(ttEntry) // we have a match in the transposition table with a greater depth
	{
        // If info in the entry is valuable, use it
        if (ttEntry->getNodeType() == NodeType::EXACT)
        {
        	myBestMove = ttEntry->getBestmove();
            return ttEntry->getScore();
        }
	}

	MoveGen moveGen(myBoard);
	std::vector<Move> moveList = moveGen.generateMoves();

	myMoveOrder.rateMoves(moveList, myBoard, myPly, true);
	myMoveOrder.sortMoves(moveList);

	for (auto currentMove : moveList)
	{
		myBoard->executeMove(currentMove);
		myEval.updateEvalAttributes(currentMove);
		myPly++;

		score = -negaMax(depth - 1, -beta, -alpha);

		if( score > alpha )
		{
			alpha = score;
			myBestMove = currentMove.getMove16();
		}

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);
		myPly--;
	}

	globalTT.setTTEntry(myBoard->key, depth, alpha, NodeType::EXACT, myBestMove, myBoard->myHalfMovesCounter);

	return alpha;
}

int Search::negaMaxRootIterativeDeepening(const int allocatedTimeMS)
{
    clearSearchData();

	int alpha = -999999;
	int beta = -alpha;
	int score = 0;
	myMovesSearched = 0;
	myPly=1;

	//Starting time
	std::chrono::high_resolution_clock::time_point startTime =
			std::chrono::high_resolution_clock::now();

	int depth = 1;

	while(true)
	{
		alpha = -999999;
		beta = -alpha;
		score = 0;

		std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();
		auto dur = time - startTime;
		int durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

		//check for time
		if(depth !=1)
		{
			if(durationMS > 0.3*allocatedTimeMS) return alpha; //if there only 2/3 of time left don't go one depth further
		}

		auto currentKey = myBoard->key;
		auto ttEntry = globalTT.probeTT(currentKey, depth); // returns non nullpr if key exists and depth is greater
		
		if(ttEntry) // we have a match in the transposition table with a greater depth
		{
	        // If info in the entry is valuable, use it
	        if (ttEntry->getNodeType() == NodeType::EXACT)
	        {
	        	myBestMove = ttEntry->getBestmove();
	        	alpha = ttEntry->getScore();
	        }
		}
		else
		{
			MoveGen moveGen(myBoard);

			std::vector<Move> moveList = moveGen.generateMoves();
			myMoveOrder.rateMoves(moveList, myBoard, myPly, true);
			myMoveOrder.sortMoves(moveList);

			for (auto currentMove : moveList)
			{
				myBoard->executeMove(currentMove);
				myEval.updateEvalAttributes(currentMove);
				myPly++;

				score = -negaMax(depth - 1, -beta, -alpha);

				if( score > alpha )
				{
					alpha = score;
					myBestMove = currentMove.getMove16();
					//std::cout << " Romain myBestMove" << currentMove.toShortString() << std::endl;

				}
				myBoard->undoMove(currentMove);
				myEval.rewindEvalAttributes(currentMove);
				myPly--;
			}

			globalTT.setTTEntry(myBoard->key, depth, alpha, NodeType::EXACT, myBestMove, myBoard->myHalfMovesCounter);
		}

		depth++;
	}

	return alpha;
}

int Search::evaluate()
{
	myMovesSearched++;
	return (-2*myBoard->getColorToPlay() + 1)*myEval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}
