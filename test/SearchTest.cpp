#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "Search.hpp"
#include "TT.hpp"


TEST_CASE( "Don't stalemate if you can win", "[search]" )
{
    extern TT tt;
	MagicMoves::initmagicmoves();
	Tables::init();
    tt.clearTT();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("7k/8/7K/8/8/8/8/5R2 w - - 51 142"));
	Search search(sp);
	search.negaMaxRoot(5);
	Move move = search.myBestMove;

	REQUIRE(move.toShortString() == "f1f8");
}

TEST_CASE( "Search", "[search]" )
{
    extern TT tt;
	MagicMoves::initmagicmoves();
	Tables::init();
    tt.clearTT();

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
