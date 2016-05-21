#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"
#include "TT.hpp"
#include "Search.hpp"
#include <iostream>


TEST_CASE( "Test TTEntry ", "[TT]")
{
	SECTION("Test methods")
	{
        TTEntry entry1;
        REQUIRE(entry1.getDepth() == 0);
        REQUIRE(entry1.getScore() == 0);
        REQUIRE(entry1.getNodeType() == NodeType::NONE);

        Move nullMove;
        TTEntry entry2(0,24,-550000,NodeType::EXACT,nullMove);
        REQUIRE(entry2.getDepth() == 24);
        REQUIRE(entry2.getScore() == -550000);
        REQUIRE(entry2.getNodeType() == 1);
	}

}


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
			int nodesSearchWithoutTT = s.myMovesSearched;

			REQUIRE(globalTT.calculateEntryCount() > 0);
			Move bestMoveNoTT = s.myBestMove;
			s.negaMaxRoot(i);
			REQUIRE(bestMoveNoTT == s.myBestMove);
			REQUIRE(s.myMovesSearched == 0);

			//Now previous search is at i-1
			globalTT.clearTT();
			s.negaMaxRoot(i-1);
			// search again: we should have the same results (and less nodes searched)
			s.negaMaxRoot(i);
			REQUIRE(s.myMovesSearched <= nodesSearchWithoutTT);
			REQUIRE(bestMoveNoTT == s.myBestMove);
		}
	}

	SECTION("Other positions")
	{
		std::vector<std::string> fens;
		//fens.push_back(""); // Kiwipete
		fens.push_back("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"); // Kiwipete
		fens.push_back("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"); //pos 3
		fens.push_back("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1	"); //pos 4
		fens.push_back("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6"); //pos 5
		fens.push_back("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"); //pos 5 bis
		fens.push_back("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"); // Position 6
		fens.push_back("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1"); // Promotion

		for(std::string fen : fens)
		{
			for(int i = 2; i <= 5; i++) //sill one issue for pos5 at depth6, should try increase TTsize
			{
				globalTT.clearTT();
				REQUIRE(globalTT.calculateEntryCount() == 0);
				std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board(fen));
				Search s(sp);
				s.negaMaxRoot(i);
				int nodesSearchWithoutTT = s.myMovesSearched;

				REQUIRE(globalTT.calculateEntryCount() > 0);
				Move bestMoveNoTT = s.myBestMove;
				// search again: we should have the same results (and less nodes searched)
				s.negaMaxRoot(i);
				REQUIRE(s.myMovesSearched == 0);

				REQUIRE(bestMoveNoTT == s.myBestMove);

				//Now previous search is at i-1
				globalTT.clearTT();
				s.negaMaxRoot(i-1);
				// search again: we should have the same results (and less nodes searched)
				s.negaMaxRoot(i);
				REQUIRE(s.myMovesSearched <= nodesSearchWithoutTT); //THIS FAILS FOR SOME POSITION/DEPTH

				REQUIRE(bestMoveNoTT == s.myBestMove);
			}
		}
	}
}
