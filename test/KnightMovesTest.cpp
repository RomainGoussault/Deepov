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
#include "MoveGen.hpp"


TEST_CASE( "Knight moves", "[knight]" )
{
    Tables::init();

	SECTION("Test pseudo-legal moves with one knight")
	{
		Board board("8/4kB2/8/5b2/8/1bqKN3/8/n7 w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKnightPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKnightPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 8);
		REQUIRE(blackSize == 1);
	}

	SECTION("Test pseudo-legal moves with 2 knights")
	{
		Board board("8/1N6/3q4/8/3r4/3B4/8/7N w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKnightPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKnightPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 6);
		REQUIRE(blackSize == 0);
	}
}
