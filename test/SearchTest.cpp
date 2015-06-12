#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "Search.hpp"

TEST_CASE( "Search", "[search]" )
{
	initmagicmoves();

	SECTION("Test search depth 1")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn3r2/8/8/2p2Q2/8/NN6/KN6 w - -"));
		Search search(sp);
		search.negaMaxRoot(1,0,0);
		Move move = search.myBestMove;

		REQUIRE(move.toShortString() == "f4f7");
	}

	SECTION("Test search depth 2")
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn2rr2/8/4Q3/8/2p1p2b/1Q6/KN6 w - -"));
		Search search(sp);
		search.negaMaxRoot(2,0,0);
		Move move = search.myBestMove;

		REQUIRE(move.toShortString() == "e5c3");
	}
}
