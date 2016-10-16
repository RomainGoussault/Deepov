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


TEST_CASE( "knight check" )
{
	Tables::init();
	Board fb = Board("8/8/k7/2N5/8/8/4K3/1n6 b - -");
	fb.updateKingAttackers();

	REQUIRE(fb.isCheck() == true);
	fb = Board("8/8/k7/2N5/8/8/4K3/1n6 w - -");
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "rook check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("7n/8/k2R4/3r4/8/8/4K3/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("7n/8/k2R4/3r4/8/8/4K3/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "bishop check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("2B3Rn/1r6/k7/8/2b5/8/4K3/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("2B3Rn/1r6/k7/8/2b5/8/4K3/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

TEST_CASE( "queen check" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	Board fb = Board("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);
}

TEST_CASE( "king check" )
{
	Tables::init();
	Board fb = Board("8/8/1k6/8/8/3K4/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/1k6/8/8/3K4/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/8/8/2k5/3K4/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("8/8/8/8/2k5/3K4/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

TEST_CASE( "pawn check" )
{
	Tables::init();

	Board fb = Board("8/8/8/8/2k2p2/6K1/2P5/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == false);

	fb = Board("8/8/8/8/2k2p2/6K1/2P5/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("2k5/3P3p/6K1/8/8/8/8/8 b - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);

	fb = Board("2k5/3P3p/6K1/8/8/8/8/8 w - -");
	fb.updateKingAttackers();
	REQUIRE(fb.isCheck() == true);
}

