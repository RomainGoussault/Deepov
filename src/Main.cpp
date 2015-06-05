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
#include "FastBoard.hpp"
#include "MoveGen.hpp"
#include "Board.hpp"
#include "FastMove.hpp"
#include "MagicMoves.hpp"

int main() {

	initmagicmoves();
	FastBoard fb("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//	Board b = Board("rnbqkbnr/1ppppppp/p7/P7/8/8/1PPPPPPP/RNBQKBNR b KQkq -");
//	std::cout << fb.divide(6) << std::endl;
//	std::cout << b.divide(3) << std::endl;

	std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();

	std::cout << fb.perft(5) << std::endl;
	//Romain 4.4 sec

	std::chrono::high_resolution_clock::time_point t2 =
			std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<
			std::chrono::duration<double>>(t2 - t1);

	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << std::endl;

	//std::shared_ptr<FastBoard> board = std::make_shared<FastBoard>("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
	// MoveGen moveGen(board);
//	std::cout << board << std::endl;

	//int origin = 53; // F7
//	int destination = 37; // F5

//	std::cout <<"size move history" << std::endl;
//	std::cout << board->getMovesHistory().size() << std::endl;
//	std::cout << moveGen.getMovesHistory().size() << std::endl;
//
//	FastMove move(origin, destination, FastMove::DOUBLEPAWNPUSH_FLAG, FastMove::PAWN_TYPE);
//	board->executeMove(move);
////	std::cout << board << std::endl;
//
//	std::cout <<"size move history" << std::endl;
//	std::cout << board->getMovesHistory().size() << std::endl;
//	std::cout << moveGen.getMovesHistory().size() << std::endl;

	/*
	 boost::optional<FastMove> lastMove(board.getEnemyLastMove());

	 std::cout <<"lastMove" << std::endl;
	 std::cout << lastMove << std::endl;

	 std::vector<FastMove> epMoves = moveGen.getWhiteEnPassantMoves();
	 int epSize = epMoves.size();


	 std::cout <<"ep size" << std::endl;
	 std::cout << epSize << std::endl;

	 //	MoveGen moveGen(fb);
	 //
	 //	std::cout << fb << std::endl;
	 //	std::cout << moveGen.isQueenSideCastlingPossible(WHITE) << std::endl;


	 /*	FastBoard fb = FastBoard("8/8/8/8/8/8/4n3/3Rrn2 b - -");

	 int size = fb.getRookPseudoLegalMoves(BLACK).size();
	 std::cout << size << std::endl;


	 std::cout << fb << std::endl;

	 FastMove move = fb.getRookPseudoLegalMoves(BLACK)[0];
	 fb.executeMove(move);

	 std::cout << fb << std::endl;

	 fb.undoMove(move);

	 std::cout << fb << std::endl;*/

	return 0;
}
