/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Search.hpp"
#include "Eval.hpp"
#include "TT.hpp"

#include <chrono>
#include <ctime>
#include <ratio>
#include <algorithm>

Search::Search(std::shared_ptr<Board> boardPtr) : myBestMove(),myMovesSearched(0), myEval(boardPtr),myMoveOrder(),myPly(0),myPvTable{0},myPvLength{0}
{
	myBoard = boardPtr;
}

void Search::clearSearchData()
{
    // Clear the killer when starting a new search
    myMoveOrder.clearKillers();
    // Clear other things (TODO)
}

bool Search::isInsufficentMatingMaterial() const
{
	// KvK, KvK+B, K+BvK+B, same with B=N 
	bool isPawns = myBoard->getAllPawns();
	bool isQueensOrRooks = myBoard->getAllQueens() || myBoard->getAllRooks();
	auto numberOfWhiteMinorPieces = popcount(myBoard->getWhiteKnights() | myBoard->getWhiteBishops());
	auto numberOfBlackMinorPieces = popcount(myBoard->getBlackKnights() | myBoard->getBlackBishops());

	//No pawns, no queens nor rooks, only one bishop or knight per side.
	return !isPawns && !isQueensOrRooks && numberOfWhiteMinorPieces <= 1 && numberOfBlackMinorPieces <=1;
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
	//Default no null move
	return negaMax(depth, alpha, beta, false);
}

int Search::negaMax(const int depth, int alpha, const int beta, const bool isNullMoveAuth)
{
	int alpha_old = alpha;
	int extensions = 0;
    myPvLength[myPly] = myPly; // Currentlength of the local PV 

	//Check extension: If in check go one ply further
	myBoard->updateKingAttackers(myBoard->getColorToPlay());	
	if(myBoard->isCheck() && myPly <= MAX_DEPTH) extensions++;

	if (depth + extensions <= 0) // If we call negaMaxRoot at depth = 0 , depth =-1
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
	std::vector<Zkey> keys = myBoard->getKeysHistory();
	Zkey currentKey = myBoard->key;
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

	/* Conditions for trying Null Move Pruning (from Faile)
       - not in check
       - we didn't just make a null move (bool isNullMoveAuth)
       - we don't have a risk of zugzwang by being in the endgame
       - depth is >= R + 1
       what we do after null move:
       - TODO: if score is close to -mated, we're in danger, increase depth
       - if score is >= beta, we can get an early cutoff and exit */
    const int R = 3;
    
    U64 heavyPieces = myBoard->getQueens(myBoard->getColorToPlay()) | myBoard->getRooks(myBoard->getColorToPlay()) | myBoard->getBishops(myBoard->getColorToPlay()) | myBoard->getKnights(myBoard->getColorToPlay());
    if(isNullMoveAuth && !myBoard->isCheck() && heavyPieces && depth >= R+1)
    {
    	//Do null move
		myBoard->executeNullMove();

    	int nullScore = -negaMax(beta, -beta+1, depth-1-R, false);

		// //Undo null move 	
		myBoard->undoNullMove();

		if(nullScore >= beta)
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

    auto moveNumber = 0;
	for (auto currentMove : moveList)
	{
		moveNumber++;

		bool isEscapingCheck = myBoard->isCheck(); 
		myBoard->executeMove(currentMove);
		myEval.updateEvalAttributes(currentMove);
		myPly++;

		myBoard->updateKingAttackers();

		// Late Move Reductions (LMR): Reduce moves that we suppose are bad.
		// The necessary condictions to perform LMR are:
		// Not for the first 4 moves (they are supposed to be good, thanks to our move ordering)
		// ply > 4
		// not a capture/promotion move
		// not in check, doesn't give check
		// not in a PV node (TODO)
		if(myPly > 3 && moveNumber >= 4 && !currentMove.isCapture() && !currentMove.isPromotion() && !myBoard->isCheck() && !isEscapingCheck)
		{
			int lmrScore = -negaMax(depth - 2, -beta, -alpha);
			if(lmrScore >= alpha) //do a research
			{
				//Do a research
				score = -negaMax(depth - 1, -beta, -alpha);
			}
			else
			{
				score = lmrScore;
			}
		}
		else
		{
			score = -negaMax(depth + extensions - 1, -beta, -alpha);
		}

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);   
		myPly--;

		if(score >= beta)
		{
			//update killer and TT
			myMoveOrder.setNewKiller(currentMove,myPly);
			globalTT.setTTEntry(currentKey, depth, score, NodeType::LOWER, currentMove.getMove16(), myBoard->getPly());
			return beta;   //  fail hard beta-cutoff
		}

        if (score > bestScore) 
        {
            bestScore = score ;
            bestMove = currentMove ;
		    if( score > alpha )
		    {
			    alpha = score ; // alpha acts like max in MiniMax
                // Save the pv at each ply
                myPvTable[myPly][myPly] = currentMove ; 
                for (unsigned int i=myPly+1; i<myPvLength[myPly+1]; i++)
                {
                    myPvTable[myPly][i] = myPvTable[myPly+1][i] ; // copy the pv from deeper ply
                }
                myPvLength[myPly] = myPvLength[myPly+1];
		    }
        }
	}

	  // store hash info
	  if (alpha > alpha_old)
			globalTT.setTTEntry(currentKey, depth, bestScore, NodeType::EXACT, bestMove.getMove16(), myBoard->getPly());
	  else
			globalTT.setTTEntry(currentKey, depth, alpha, NodeType::UPPER, bestMove.getMove16(), myBoard->getPly());


	return alpha;
}

int Search::negaMaxRoot(const int depth)
{
    clearSearchData();

	int alpha = -999999;
	int beta = -alpha;
	int score = 0;
	myMovesSearched = 0;
	myPly=0;
    myPvLength[myPly] = myPly; // Current length of the local PV 

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

		myBoard->undoMove(currentMove);
		myEval.rewindEvalAttributes(currentMove);
		myPly--;

		if( score > alpha )
		{
			alpha = score;
			myBestMove = currentMove.getMove16();
            // Save the pv
            myPvTable[myPly][myPly] = currentMove ; 
            for (unsigned int i=myPly+1; i<myPvLength[myPly+1]; i++)
            {
                myPvTable[myPly][i] = myPvTable[myPly+1][i] ; // copy the pv from the deeper ply
            }
            myPvLength[myPly] = myPvLength[myPly+1]; // update the length of the PV to the one assigned
		}
	}

	globalTT.setTTEntry(myBoard->key, depth, alpha, NodeType::EXACT, myBestMove, myBoard->getPly());

	return alpha;
}

int Search::negaMaxRootIterativeDeepening(const unsigned int allocatedTimeMS)
{
    clearSearchData();

	int alpha = -999999;
	int beta = -alpha;
	int score = 0;
	unsigned int minDepth = 2;
	
	myMovesSearched = 0;
	myPly=0;
    myPvLength[myPly] = myPly; // Current length of the local PV

	//Starting time
	std::chrono::high_resolution_clock::time_point startTime =
			std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point time;
	auto dur = time - startTime;

	myDepth = 1;

	while(true)
	{
		alpha = -999999;
		beta = -alpha;
		score = 0;
        bool isPvs = false;

		
		//check for time
		if (mySearchDurationMS > 0.5 * allocatedTimeMS && myDepth >= minDepth)
		{
			return alpha;
		}
		auto currentKey = myBoard->key;
		auto ttEntry = globalTT.probeTT(currentKey, myDepth); // returns non nullpr if key exists and depth is greater
		
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

			unsigned int j = 0;
			for (auto currentMove : moveList)
			{
				j++;

				bool isMovelistHalfDone = 2*j > moveList.size();
				
				// Check for time fist
				time = std::chrono::high_resolution_clock::now();
				dur = time - startTime;
				mySearchDurationMS = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();

				if(mySearchDurationMS >  allocatedTimeMS && myDepth >= minDepth && isMovelistHalfDone)
				{
					return alpha;
				}

				myBoard->executeMove(currentMove);
				myEval.updateEvalAttributes(currentMove);
				myPly++;

                if (isPvs) {
                    score = -negaMax(myDepth - 1, -alpha - 1, -alpha);

                    if ((score > alpha) && (score < beta)) // Check for failure.
                    {
                        score = -negaMax(myDepth - 1, -beta, -alpha);
                    }
                } 
                else
                {
				    score = -negaMax(myDepth - 1, -beta, -alpha);
                }

				if( score > alpha )
				{
					alpha = score;
                    isPvs = true ;
					myBestMove = currentMove.getMove16();
                    myPvTable[myPly][myPly] = currentMove ; 
                    for (unsigned int i=myPly+1; i<myPvLength[myPly+1]; i++)
                    {
                        myPvTable[myPly][i] = myPvTable[myPly+1][i] ;
                    }
                    myPvLength[myPly] = myPvLength[myPly+1];
				}
			
				myBoard->undoMove(currentMove);
				myEval.rewindEvalAttributes(currentMove);
				myPly--;
			} 


			globalTT.setTTEntry(myBoard->key, myDepth, alpha, NodeType::EXACT, myBestMove, myBoard->getPly());
		}

		//update duration and send info to UCI
		time = std::chrono::high_resolution_clock::now();
		dur = time - startTime;

		mySearchDurationMS = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
		mySearchDurationMS = std::max(mySearchDurationMS, (unsigned int) 1); 
		sendInfoToUCI(alpha);

		myDepth++;
	}

	return alpha;
}

int Search::evaluate()
{
	myMovesSearched++;
	return (-2*myBoard->getColorToPlay() + 1)*myEval.evaluate(); //evaluate()/* returns +evaluate for WHITE, -evaluate for BLACK */
}

void Search::sendInfoToUCI(int alpha)
{
	// Send info to uci console
	std::cout << "info";
	std::cout << " depth " << myDepth;
	std::cout << " score cp " << alpha;
	std::cout << " nodes " << myMovesSearched;
	unsigned int nps = 1000 * myMovesSearched / mySearchDurationMS;
	std::cout << " nps " << nps;
	std::cout << " time " << mySearchDurationMS;
//	std::cout << " pv "; TODO
	std::cout << std::endl;
}

void Search::printPvTable(const unsigned int numLines)
{
    unsigned int j;
	for(unsigned int i = 0; i<=numLines; i++) // For each ply starting at 0 (root) to numLines
	{
        for (j=0; j<i; j++)
        {
            std::cout << "       ";
        }
        j=i;
        while (!myPvTable[i][j].isNullMove()) // Print successives moves until first null move
		{
			std::cout << myPvTable[i][j].toShortString() << "   ";
            j++;
		}
		std::cout << std::endl;
	}
}
