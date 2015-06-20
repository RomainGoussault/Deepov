#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "Uci.hpp"
#include "Search.hpp"

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
		m = strToMove(token);

		if(m.getOrigin() != 0 &&  m.getDestination() != 0) //bad way of checking if move is legal
			boardPtr->executeMove(m);
	}
}

Move Uci::strToMove(std::string str)
{
	MoveGen mg(boardPtr);
	std::vector<Move> moves = mg.getLegalMoves();


	for (auto move : moves)
	{
		std::cout << move.toShortString() << std::endl;
		if(str == move.toShortString()) return move;
	}

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
			std::cout << "id name Deepov" << std::endl;
			std::cout << "id author Romain Goussault - Navid Hedjazian" << std::endl;
			std::cout << "uciok" << std::endl;
		}
		else if (token == "isready")

			std::cout << "readyok" << std::endl;

		else if (token == "ucinewgame")

			; // nothing to do

		else if (token == "position")
			updatePosition(is);

		else if (token == "print")
			std::cout << *boardPtr << std::endl;

		else if (token == "go")
		{
			Search search(boardPtr);
			search.negaMaxRoot(5,0,0);
			Move move = search.myBestMove;
			std::cout << "bestmove " << move.toShortString() << std::endl;
		}
		else
			// Command not handled
			std::cout << "what?" << std::endl;
	}
}
