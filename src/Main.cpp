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

#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

#include "Types.hpp"
#include "Eval.hpp"
#include "Search.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"
#include "Utils.hpp"
#include "Uci.hpp"
#include "TT.hpp"

//#define PERFORMANCE_TEST


int main() {

//	//global transposition table
//	extern TT tt;
	MagicMoves::initmagicmoves();
	Tables::init();



		//	std::string fen = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"; //pos 3 init
			std::string fen = "8/2p5/3p4/KP5r/5R1k/8/4P1P1/8 b - -"; //pos 3 + 1 move
		//	std::string fen = "8/2p5/3p4/KP4kr/5R2/8/4P1P1/8 w - -"; //pos 3 + 2 move



	
int i = 3;
				std::cout << "depth " << i << std::endl;

				globalTT.clearTT();
				std::cout << " " << std::endl;

				//REQUIRE(globalTT.calculateEntryCount() == 0);
				std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board(fen));
				Search s(sp);
				s.negaMaxRoot(i);
				int nodesSearchWithoutTT = s.myMovesSearched;

				std::cout << "nodes searched no TT depth i: " << s.myMovesSearched << std::endl;

				//REQUIRE(globalTT.calculateEntryCount() > 0);
				Move bestMoveNoTT = s.myBestMove;
				// search again: we should have the same results (and less nodes searched)
				s.negaMaxRoot(i);
				//REQUIRE(s.myMovesSearched == 0);
				std::cout << " " << std::endl;

				std::cout << "nodes searched TT depth i:" << s.myMovesSearched << std::endl;
				std::cout << " " << std::endl;

				//REQUIRE(bestMoveNoTT == s.myBestMove);

				//Now previous search is at i-1
				globalTT.clearTT();
				s.negaMaxRoot(i-1);
				std::cout << "nodes searched TT depth i-1:" << s.myMovesSearched << std::endl;

				// search again: we should have the same results (and less nodes searched)
				std::cout << "entry count TT depth i-1:" << globalTT.calculateEntryCount() << std::endl;
				std::cout << globalTT << std::endl;
				std::cout << " " << std::endl;

				s.negaMaxRoot(i);
				//REQUIRE(s.myMovesSearched <= nodesSearchWithoutTT); //THIS FAILS FOR SOME POSITION/DEPTH

				std::cout << "nodes searched TT depth i:" << s.myMovesSearched << std::endl;
				std::cout <<  std::endl;
				std::cout << bestMoveNoTT << std::endl;

				//REQUIRE(bestMoveNoTT == s.myBestMove);

				std::cout << "entry count TT depth i-1:" << globalTT.calculateEntryCount() << std::endl;
				std::cout << globalTT << std::endl;
				std::cout << " " << std::endl;

//				s.negaMaxRoot(i-1);
//				std::cout << "nodes searched TT depth i-1 :" << s.myMovesSearched << std::endl;

//                s.negaMaxRoot(i);
//				std::cout << "nodes searched TT depth i again:" << s.myMovesSearched << std::endl;



	#ifdef PERFORMANCE_TEST

		Utils::getPerformanceIndicator();

	#else

		Uci uci;
		uci.loop();

	#endif

	return 0;
}
