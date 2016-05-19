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




			for(int i = 6; i <= 6; i++)
			{
				std::cout << "i: " << i << std::endl;
				globalTT.clearTT();
				std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"));
				Search s(sp);
				s.negaMaxRoot(i);
				int nodesSearchWithoutTT = s.myMovesSearched;
				std::cout << "nodesSearchWithoutTT: " << nodesSearchWithoutTT << std::endl;
				std::cout << "" << std::endl;

				Move bestMoveNoTT = s.myBestMove;
				// search again: we should have the same results (and less nodes searched)
				//s.negaMaxRoot(i);


				//Now previous search is at i-1
				globalTT.clearTT();
				s.negaMaxRoot(i-1);
				std::cout << "s.negaMaxRoot(i-1): " << nodesSearchWithoutTT << std::endl;
				//std::cout << globalTT << std::endl;

				std::cout << "" << std::endl;
				// search again: we should have the same results (and less nodes searched)
				s.negaMaxRoot(i);
				std::cout << "myMovesSearched: " << s.myMovesSearched << std::endl << "nodesSearchWithoutTT: " << nodesSearchWithoutTT << std::endl;
			}


	#ifdef PERFORMANCE_TEST

		Utils::getPerformanceIndicator();

	#else

		// Uci uci;
		// uci.loop();

	#endif

	return 0;
}
