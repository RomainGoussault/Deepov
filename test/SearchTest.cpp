#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "Search.hpp"


TEST_CASE( "Don't stalemate if you can win", "[search]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

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
}
