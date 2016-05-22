#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <thread>         // std::thread


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
		myBoardPtr = std::shared_ptr<Board>(new Board());
		//is >> token; // Consume "moves" token if any
	}
	else if (token == "fen")
	{
		while (is >> token && token != "moves")
			fen += token + " ";
		myBoardPtr = std::shared_ptr<Board>(new Board(fen));
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
			myBoardPtr->executeMove(m);
		}
	}
}

std::string Uci::getOption(const std::string str) const
{
	//Ugly and not safe
	//TODO: Refactor
	UciOption uciOption = (*(myOptionsMap.find(str))).second;
	return uciOption.getCurrentValue();
}

// setoption() is called when engine receives the "setoption" UCI command. The
// function updates the UCI option ("name") to the given value ("value").
// Taken and adaptated from Stockfish
void Uci::setoption(std::istringstream& is) {

	std::string token, name, value;

	is >> token; // Consume "name" token

	// Read option name (can contain spaces)
	while (is >> token && token != "value")
		name += std::string(" ", name.empty() ? 0 : 1) + token;

	// Read option value (can contain spaces)
	while (is >> token)
		value += std::string(" ", value.empty() ? 0 : 1) + token;

	if (myOptionsMap.count(name))
	{
		//count returns the number of elements with key name
		// which is either 1 or 0 since this container does not allow duplicates

		//This calls the overloaded operator: UciOption& operator=
		myOptionsMap[name] = value;

		std::cout << "Option: " << name << " updated to "<< value << std::endl;

	}
	else
		std::cout << "No such option: " << name << std::endl;
}

void Uci::printOptions() const{

	std::cout << "Current options" << std::endl;


	for(auto elem : myOptionsMap)
	{
		UciOption uciOption = elem.second;

		std::cout << "option name " << elem.first << " type spin default "  <<  uciOption.getDefaultValue()
				<< " min " << uciOption.getMin() << " max " << uciOption.getMax() << std::endl;
	}
}

Move Uci::strToMove(std::string str)
{
	MoveGen mg(myBoardPtr);
	std::vector<Move> moves = mg.generateLegalMoves();


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

	printOptions();

	while (std::getline(std::cin, line))
	{
		std::istringstream is(line);

		token.clear(); // getline() could return empty or blank line
		is >> std::skipws >> token;
		//	std::cout << token << std::endl;

		if (token == "uci")
		{
			std::cout << "id name Deepov 0.4" << std::endl;
			std::cout << "id author Romain Goussault - Navid Hedjazian" << std::endl;
			printOptions();
			std::cout << "uciok" << std::endl;
		}
		else if (token == "isready")
		{
			globalTT.clearTT();
			std::cout << "readyok" << std::endl;
		}
		else if (token == "setoption") 
            setoption(is);

		else if (token == "color")

			std::cout << "colorToPlay: " << myBoardPtr->getColorToPlay() << std::endl;

		else if (token == "ucinewgame")
            globalTT.clearTT();

		else if (token == "position")
			updatePosition(is);

		else if (token == "print")
			std::cout << *myBoardPtr << std::endl;

		else if (token == "printOptions")
			printOptions();

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
		}
		else if (token == "quit")
		{
			std::cout << "Terminating.." << std::endl;
			break;
		}
		else
			// Command not handled
			std::cout << "what?" << std::endl;
	}
}

void Uci::search()
{
	Search search = Search(myBoardPtr); //Note this could be done earlier before the search

	TimeManager::divider = std::stoi(getOption("timeDivider"));
	Eval::POSITIONNAL_GAIN_PERCENT = std::stoi(getOption("positionnalGain"));
	Eval::MOBILITY_GAIN_PERCENT = std::stoi(getOption("mobilityGain"));
    // Defines TT size here 

	auto timeMS = TimeManager::getTimeAllocatedMiliSec(wtime, btime,  winc,  binc, myBoardPtr->getColorToPlay());
	//std::cout << "Romain time allocated " << timeMS << std::endl;

	search.negaMaxRootIterativeDeepening(timeMS);

	Move bestMove = search.myBestMove;
	std::cout << "bestmove " << bestMove.toShortString() << std::endl;
}
