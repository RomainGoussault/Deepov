
#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html
using namespace std;

class Uci
{
public :

	std::shared_ptr<Board> sp;

	Uci()//Default constructor
	{
		sp = std::shared_ptr<Board>(new Board());
	}

	void updatePosition(std::istringstream& is)
	{
		Move m;
		string token, fen;

		is >> token;

		if (token == "startpos")
		{
			sp = std::shared_ptr<Board>(new Board());
			//is >> token; // Consume "moves" token if any
		}
		else if (token == "fen")
		{
			while (is >> token && token != "moves")
				fen += token + " ";
			sp = std::shared_ptr<Board>(new Board(fen));
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
			sp->executeMove(m);
		}
	}

	Move strToMove(std::string str)
	{
		MoveGen mg(sp);
		std::vector<Move> moves = mg.getLegalMoves();


		for (auto move : moves)
		{
			std::cout << move.toShortString() << std::endl;
			if(str == move.toShortString()) return move;
		}

		Move m = Move();
		return m;
	}

	void loop()
	{
		string line;
		string token;

		// Make sure that the outputs are sent straight away to the GUI
		cout.setf (ios::unitbuf);

		while (getline (cin, line))
		{
			istringstream is(line);

			token.clear(); // getline() could return empty or blank line
			is >> skipws >> token;
		//	std::cout << token << std::endl;

			if (token == "uci")
			{
				cout << "id name Deepov" << endl;
				cout << "id author Romain Goussault - Navid Hedjazian" << endl;
				cout << "uciok" << endl;
			}
			else if (token == "isready")

				cout << "readyok" << endl;

			else if (token == "ucinewgame")

				; // nothing to do

			else if (token == "position")
				updatePosition(is);

			else if (token == "print")
				std::cout << *sp << std::endl;

			else if (token == "go")
			{
				Search search(sp);
				search.negaMaxRoot(4,0,0);
				Move move = search.myBestMove;
				std::cout << "bestmove " << move.toShortString() << std::endl;
			}
			else
				// Command not handled
				cout << "what?" << endl;
		}
	}
};


#endif /* UCI_HPP_ */
