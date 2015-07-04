#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "Uci.hpp"
#include "Search.hpp"
#include "TimeManager.hpp"


//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html

void Uci::updatePosition(std::istringstream& is)
{
	Move m;
	std::string token, fen;

	is >> token;

	if (token == "startpos")
	{
		boardPtr = std::shared_ptr<Board>(new Board());
		//is >> token; // Consume "moves" token if any
	}
	else if (token == "fen")
	{
		while (is >> token && token != "moves")
			fen += token + " ";
		boardPtr = std::shared_ptr<Board>(new Board(fen));
	}
	else
	{
		return;
	}

	// Parse move list (if any)
	while (is >> token)
	{
		if (token != "moves")
		{
			m = strToMove(token);
			boardPtr->executeMove(m);
		}
	}
}

Move Uci::strToMove(std::string str)
{
	MoveGen mg(boardPtr);
	std::vector<Move> moves = mg.getLegalMoves();


	for (auto move : moves)
	{
		if(str == move.toShortString()) return move;
	}

	std::cout << " PROBLEM [" << str << "]" <<std::endl;

	Move m = Move();
	return m;
}

void Uci::loop()
{
	std::string line;
	std::string token;

	// Make sure that the outputs are sent straight away to the GUI
	std::cout.setf (std::ios::unitbuf);

	while (std::getline(std::cin, line))
	{
		std::istringstream is(line);

		token.clear(); // getline() could return empty or blank line
		is >> std::skipws >> token;
		//	std::cout << token << std::endl;

		if (token == "uci")
		{
			std::cout << "id name Deepov 0.2 beta" << std::endl;
			std::cout << "id author Romain Goussault - Navid Hedjazian" << std::endl;
			std::cout << "uciok" << std::endl;
		}
		else if (token == "isready")

			std::cout << "readyok" << std::endl;

		else if (token == "color")

			std::cout << "colorToPlay: " << boardPtr->getColorToPlay() << std::endl;

		else if (token == "ucinewgame")

			; // nothing to do

		else if (token == "position")
			updatePosition(is);

		else if (token == "print")
			std::cout << *boardPtr << std::endl;

		else if (token == "go")
		{
			while (is >> token)
			{
				if (token == "wtime")     is >> wtime;
				else if (token == "btime")     is >> btime;
				else if (token == "winc")      is >> winc;
				else if (token == "binc")      is >> binc;
			}

			//http://stackoverflow.com/questions/12624271/c11-stdthread-giving-error-no-matching-function-to-call-stdthreadthread
			thrd::thread thr(&Uci::search, this);
			thrd::swap(thr, myThread);
			myThread.join();
			//1sec search only


		//	search();
		}
		else
			// Command not handled
			std::cout << "what?" << std::endl;
	}
}

void Uci::search()
{
	Search search(boardPtr); //Note this could be done earlier before the search

	int timeMS = TimeManager::getTimeAllocatedMiliSec(wtime, btime,  winc,  binc, boardPtr->getColorToPlay());
	//std::cout << "Romain time allocated " << timeMS << std::endl;

	search.negaMaxRootIterativeDeepening(timeMS);

	Move bestMove = search.myBestMove;
	std::cout << "bestmove " << bestMove.toShortString() << std::endl;
}
