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

	SECTION("Depth 1")
	{
		REQUIRE(globalTT.calculateEntryCount() == 0);

		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
		Search s(sp);
		s.negaMaxRoot(1);

		REQUIRE(globalTT.calculateEntryCount() == 1);
		globalTT.clearTT();
		REQUIRE(globalTT.calculateEntryCount() == 0);
	}

	SECTION("Depth 2")
	{
		REQUIRE(globalTT.calculateEntryCount() == 0);

		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
		Search s(sp);
		s.negaMaxRoot(2);

		REQUIRE(globalTT.calculateEntryCount() > 1);
		globalTT.clearTT();
		REQUIRE(globalTT.calculateEntryCount() == 0);
	}
}

TEST_CASE( "Search results should be the same with or without TT ", "[TT]")
{
	MagicMoves::initmagicmoves();
	Tables::init();
	globalTT.clearTT();

	SECTION("Initial position")
	{
		for(int i = 1; i <= 6; i++)
		{
			globalTT.clearTT();
			REQUIRE(globalTT.calculateEntryCount() == 0);
			std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());
			Search s(sp);
			s.negaMaxRoot(i);
			Move bestMoveNoTT = s.myBestMove;
			// search again: we should have the same results (and less nodes searched)
			s.negaMaxRoot(i);
			REQUIRE(bestMoveNoTT == s.myBestMove);

			//Now previous search is at i-1
			globalTT.clearTT();
			s.negaMaxRoot(i-1);
			// search again: we should have the same results (and less nodes searched)
			s.negaMaxRoot(i);
			REQUIRE(bestMoveNoTT == s.myBestMove);
		}
	}

	SECTION("Kiwipete position")
	{
		for(int i = 2; i <= 6; i++)
		{
			globalTT.clearTT();
			REQUIRE(globalTT.calculateEntryCount() == 0);
			std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"));
			Search s(sp);
			s.negaMaxRoot(i);
			Move bestMoveNoTT = s.myBestMove;
			// search again: we should have the same results (and less nodes searched)
			s.negaMaxRoot(i);
			REQUIRE(bestMoveNoTT == s.myBestMove);

			//Now previous search is at i-1
			globalTT.clearTT();
			s.negaMaxRoot(i-1);
			// search again: we should have the same results (and less nodes searched)
			s.negaMaxRoot(i);
			REQUIRE(bestMoveNoTT == s.myBestMove);
		}
	}
}
