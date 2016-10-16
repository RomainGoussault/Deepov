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

#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Rook moves", "[rook]" )
{
	MagicMoves::initmagicmoves();
    Tables::init();
	SECTION("Test pseudo-legal moves")
	{
		Board board("1bq1b2p/p2p1pp1/2Bk4/1N6/4r1Q1/B6P/PP1PPPPR/3K2R1 b K -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getRookPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getRookPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 11);
	}
}
