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
#include "Search.hpp"
#include "TT.hpp"


TEST_CASE( "Don't stalemate if you can win", "[search]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	ZK::initZobristKeys();
	globalTT.init_TT_size(TT::TEST_MB_SIZE); // For tests TT size is TT_SIZE_DEFAULT

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("7k/8/7K/8/8/8/8/5R2 w - - 51 142"));
	Search search(sp);
	search.negaMaxRoot(5);
	Move move = search.myBestMove;

	REQUIRE(move.toShortString() == "f1f8");
}

TEST_CASE( "Search", "[search]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	ZK::initZobristKeys();
	globalTT.init_TT_size(TT::TEST_MB_SIZE);

	SECTION("Test search depth 1 white")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn3r2/8/8/2p2Q2/8/NN6/KN6 w - -"));
		Search search(sp);
		search.negaMaxRoot(1);
		Move move = search.myBestMove;

		REQUIRE(move.toShortString() == "f4f7");
	}

	SECTION("Test search depth 1 black")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("k4K2/8/8/3q4/8/1R3N1P/8/8 b - -"));
		Search search(sp);
		search.negaMaxRoot(1);
		Move move = search.myBestMove;

		REQUIRE(move.toShortString() == "d5b3");
	}

	SECTION("Test search depth 2")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn2rr2/8/4Q3/8/2p1p2b/1Q6/KN6 w - -"));
		Search search(sp);
		search.negaMaxRoot(2);
		Move move = search.myBestMove;

		REQUIRE(move.toShortString() == "e5c3");
	}

	SECTION("Always find the quickest mate")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("8/3R4/3p4/3P4/1K4Q1/8/7k/8 w - - 97 104"));
		Search search(sp);

		for(int i = 2; i<7; i++)
		{
			search.negaMaxRoot(i);
			Move move = search.myBestMove;
			REQUIRE(move.toShortString() == "d7h7");
		}
	}
}

TEST_CASE( "Draw", "[search]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	ZK::initZobristKeys();
	globalTT.init_TT_size(TT::TEST_MB_SIZE);

	SECTION("Draw by insufficient mating material")
	{
		//K+pawns
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("8/3k1bp1/6p1/4K1P1/5P1P/2N5/8/8 b - - 36 117"));
		Search search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == false);

		//K+BvsK+N
		sp = std::shared_ptr<Board>(new Board("8/3k1b2/8/4K3/8/2N5/8/8 b - - 36 117"));
		search = Search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == true);

		//K+BBvs...
		sp = std::shared_ptr<Board>(new Board("8/3k3b/7b/4K3/8/2N5/8/8 b - - 36 117"));
		search = Search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == false);

		//K+BvsK
		sp = std::shared_ptr<Board>(new Board("8/3k1b2/8/4K3/8/8/8/8 w - - 36 117"));
		search = Search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == true);

		//KvK
		sp = std::shared_ptr<Board>(new Board("3k4/8/8/4K3/8/8/8/8 b - - 36 117"));
		search = Search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == true);

		//K+RvK
		sp = std::shared_ptr<Board>(new Board("7k/8/7K/8/8/8/8/5R2 w - - 51 142"));
		search = Search(sp);
		REQUIRE(search.isInsufficentMatingMaterial() == false);
	}
}
