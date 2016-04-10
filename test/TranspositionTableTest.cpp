#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"
#include "TT.hpp"
#include "Search.hpp"

TEST_CASE( "Fill transposition table from initial position ", "[TT]")
{
	MagicMoves::initmagicmoves();
	Tables::init();
    globalTT.clearTT();

//	SECTION("Depth 0")
//	{
//        tt.clearTT();
//		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
//		Search s(sp);
//        s.negaMaxRoot(2);
//        std::cout << "Did the search" << std::endl;
//        std::cout << tt << std::endl;

//	}

//	SECTION("Test search depth 2")
//	{
//        tt.clearTT();
//		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("kn6/nn2rr2/8/4Q3/8/2p1p2b/1Q6/KN6 w - -"));
//		Search search(sp);
//		search.negaMaxRoot(2);
//		Move move = search.myBestMove;

//		REQUIRE(move.toShortString() == "e5c3");
//        std::cout << tt << std::endl;
//	}
}
