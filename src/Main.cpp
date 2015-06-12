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

int main() {

	initmagicmoves();
	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn2rr2/8/4Q3/8/2p1p2b/1Q6/KN6 w - -"));

	Search search(sp);
	std::cout << search.negaMaxRoot(2,0,0) << std::endl;
	Move move = search.myBestMove;

	std::cout << *sp << std::endl;
	std::cout << move.toShortString()<< std::endl;

	sp->executeMove(move);

	std::cout << *sp << std::endl;
/*

	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();
	//Romain : 9sec = 995 556 Nodes/sec
	// -O3 1.6sec 5 609 501 Nodes/sec
	// Navid -O3 9sec 100 000 N/sec
	//Stockfish 180 385 601Nodes/sec

    std::string str;
    std::cin >> str;*/

	return 0;
}
