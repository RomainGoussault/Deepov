//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

#include "Color.hpp"
#include "Eval.hpp"
#include "Search.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"
#include "Utils.hpp"
#include "Uci.hpp"



int main() {

/*	MagicMoves::initmagicmoves();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("k4K2/8/8/3q4/8/1R3N1P/8/8 b - -"));

	Search search(sp);
	std::cout << search.negaMaxRoot(3,0,0) << std::endl;
	Move move = search.myBestMove;

	std::cout << *sp << std::endl;
	std::cout << move.toShortString()<< std::endl;

	sp->executeMove(move);

	std::cout << *sp << std::endl;*/
/*
	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();*/

	MagicMoves::initmagicmoves();
	Uci uci;
	uci.loop();

	//Romain :  = 2000 kNodes/sec
	// -O3  13 000 kNodes/sec

	// Navid -O3  100 000 Nodes/sec
	//Stockfish 180 385 601Nodes/sec

	return 0;
}
