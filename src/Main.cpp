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



int main() {

	MagicMoves::initmagicmoves();

	Board board("1b6/2B5/R1Pkp2R/4n3/8/3b2B1/8/3Q4 b - -");
	board.updatePinnedPieces();
	std::cout << "pinned "  << std::endl;
	std::cout << Board::printBitBoard(board.getPinnedPieces()) << std::endl;


/*




	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("k4K2/8/8/3q4/8/1R3N1P/8/8 b - -"));

	Search search(sp);
	std::cout << search.negaMaxRoot(3,0,0) << std::endl;
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
