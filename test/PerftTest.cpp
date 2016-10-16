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
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"

TEST_CASE( "Perft from initial position ", "[perft]")
{
	MagicMoves::initmagicmoves();
    Tables::init();

	SECTION("Perft 0")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(1) == 20);
	}

	SECTION("Perft 2")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(2) == 400);
	}

	SECTION("Perft 3")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(3) == 8902);
	}

	SECTION("Perft 4")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(4) == 197281);
	}

	/*SECTION("Perft 5") working but slow for unit test
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(5) == 4865609);
	}

	SECTION("Perft 6") working but slow for unit test
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(6) == 119060324);
	}*/
}

TEST_CASE( "Perft position 2 (Kiwipete)", "[perft]")
{
    Tables::init();
	MagicMoves::initmagicmoves();
    Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");

	SECTION("Perft 1")
	{
		REQUIRE(board.perft(1) == 48);
	}

	SECTION("Perft 2")
	{
		REQUIRE(board.perft(2) == 2039);
	}

	SECTION("Perft 3")
	{
		REQUIRE(board.perft(3) == 97862);
	}

	/*SECTION("Perft 4") //working but slow for unit test
	{
		REQUIRE(board.perft(4) == 4085603);
	}

	SECTION("Perft 5") working but slow for unit test
	{
		REQUIRE(board.perft(5) == 193690690);
	}*/
}

TEST_CASE( "Perft position 3 ", "[perft]")
{
	MagicMoves::initmagicmoves();
    Tables::init();

	SECTION("Perft 0")
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(1) == 14);
	}

	SECTION("Perft 2")
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(2) == 191);
	}

	SECTION("Perft 3")
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(3) == 2812);
	}

	SECTION("Perft 4")
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(4) == 43238);
	}
	/*
	SECTION("Perft 5") //working but slow for unit test
	{
		Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(5) == 674624);
	}*/
}

TEST_CASE( "Perft position 4 ", "[perft]")
{
	MagicMoves::initmagicmoves();
    Tables::init();
	Board board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	Board boardMirrored("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");


	SECTION("Perft 0")
	{
		REQUIRE(board.perft(0) == 1);
		REQUIRE(boardMirrored.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		REQUIRE(board.perft(1) == 6);
		REQUIRE(boardMirrored.perft(1) == 6);
	}

	SECTION("Perft 2")
	{
		REQUIRE(board.perft(2) == 264);
		REQUIRE(boardMirrored.perft(2) == 264);
	}

	SECTION("Perft 3")
	{
		REQUIRE(board.perft(3) == 9467);
		REQUIRE(boardMirrored.perft(3) == 9467);
	}

	/*SECTION("Perft 4") //working but slow for unit test
	{
		REQUIRE(board.perft(4) == 422333);
		REQUIRE(boardMirrored.perft(4) == 422333);
	}

	SECTION("Perft 5") //working but slow for unit test
	{
		REQUIRE(board.perft(5) == 15833292);
		REQUIRE(boardMirrored.perft(5) == 15833292);
	}*/
}

TEST_CASE( "Perft position 5 ", "[perft]") //Note The ChessProgramming website gives another FEN for this position
{
	MagicMoves::initmagicmoves();
	Tables::init();
    Board board("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");

	SECTION("Perft 1")
	{
		REQUIRE(board.perft(1) == 42);
	}

	SECTION("Perft 2")
	{
		REQUIRE(board.perft(2) == 1352);
	}

	SECTION("Perft 3")
	{
		REQUIRE(board.perft(3) == 53392);
	}
}

TEST_CASE( "Perft position 5 bis", "[perft]") //Results from stockfish
{
	MagicMoves::initmagicmoves();
	Tables::init();
    Board board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

	SECTION("Perft 1")
	{
		REQUIRE(board.perft(1) == 44);
	}

	SECTION("Perft 2")
	{
		REQUIRE(board.perft(2) == 1486);
	}

	SECTION("Perft 3")
	{
		REQUIRE(board.perft(3) ==  62379);
	}
}

TEST_CASE( "Perft position 6 ", "[perft]")
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("Perft 0")
	{
		Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(1) == 46);
	}

	SECTION("Perft 2")
	{
		Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(2) == 2079);
	}

	SECTION("Perft 3")
	{
		Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(3) == 89890);
	}
    /*
	SECTION("Perft 4") //working but slow for unit test
	{
		Board board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(4) == 3894594);
	}*/
}

TEST_CASE( "Perft Promotion", "[perft]") //Taken from http://www.rocechess.ch/perft.html
{
	MagicMoves::initmagicmoves();
	Tables::init();
    Board board("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1");

	SECTION("Perft 1")
	{
		REQUIRE(board.perft(1) == 24);
	}

	SECTION("Perft 2")
	{
		REQUIRE(board.perft(2) == 496);
	}

	SECTION("Perft 3")
	{
		REQUIRE(board.perft(3) == 9483);
	}
	/*
	SECTION("Perft 4") /working but slow for unit test
	{
		REQUIRE(board.perft(4) == 182838);
	}

	SECTION("Perft 5") //working but slow for unit test
	{
		REQUIRE(board.perft(5) == 3605103);
	}

	SECTION("Perft 6") //working but slow for unit test
	{
		REQUIRE(board.perft(6) == 71179139);
	}*/
}
