#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "is bit Set method" )
{
	//whitePawnStartingPosition
	U64 whitePawns(0 | 0xFF << 8 );

	REQUIRE(FastBoard::isBitSet(0, 5, 5) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 0, 0) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 5, 0) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 5, 5) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 7, 5) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 1, 5) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 5, 1) == true);
	REQUIRE(FastBoard::isBitSet(whitePawns, 0, 1) == true);
	REQUIRE(FastBoard::isBitSet(whitePawns, 7, 1) == true);
	REQUIRE(FastBoard::isBitSet(whitePawns, 2, 1) == true);
	REQUIRE(FastBoard::isBitSet(whitePawns, 2, 2) == false);
	REQUIRE(FastBoard::isBitSet(whitePawns, 2, 7) == false);
}

TEST_CASE( "Move methods" )
{
	FastBoard board;
	MoveGen moveGen(board);

	std::vector<FastMove> moveList = moveGen.getWhitePawnPseudoLegalMoves();
	REQUIRE(moveList.size() == 16);

	moveList = moveGen.getKingPseudoLegalMoves(WHITE);
	REQUIRE(moveList.size() == 0);

	moveList = moveGen.getKnightPseudoLegalMoves(WHITE);
	REQUIRE(moveList.size() == 4);
}
/*
TEST_CASE( "execute Move with capture" )
{
	initmagicmoves();

	FastBoard fb = FastBoard("8/8/8/8/8/8/3n4/2Nrb3 b - -");

	int size = fb.getRookPseudoLegalMoves(BLACK).size();
    REQUIRE(size == 1);

	U64 bb = fb.getBlackRooks();
    REQUIRE(FastBoard::isBitSet(bb, 6, 0) == true);
    REQUIRE(FastBoard::isBitSet(bb, 7, 0) == false);

	FastMove move = fb.getRookPseudoLegalMoves(BLACK)[0];
	fb.executeMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(FastBoard::isBitSet(bb, 6, 0) == false);
    REQUIRE(FastBoard::isBitSet(bb, 7, 0) == true);

	fb.undoMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(FastBoard::isBitSet(bb, 6, 0) == true);
    REQUIRE(FastBoard::isBitSet(bb, 7, 0) == false);
}
 */
TEST_CASE( "Perft from initial position ", "[perft]")
{
	initmagicmoves();

	SECTION("Perft 0")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(1) == 20);
	}

	SECTION("Perft 2")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(2) == 400);
	}

	SECTION("Perft 3")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(3) == 8902);
	}

	SECTION("Perft 4")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(4) == 197281);
	}

	/*SECTION("Perft 5") working but slow for unit test
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(5) == 4865609);
	}

	SECTION("Perft 6") working but slow for unit test
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(6) == 119060324);
	}*/
}
/*
TEST_CASE( "Perft position 3 ", "[perft]")
{
	initmagicmoves();

	SECTION("Perft 0")
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(1) == 14);
	}

	SECTION("Perft 2")
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(2) == 191);
	}

	SECTION("Perft 3")
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(3) == 2812);
	}

	SECTION("Perft 4")
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(4) == 43238);
	}

	SECTION("Perft 5") working but slow for unit test
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(5) == 674624);
	}
}*/

TEST_CASE( "Perft position 6 ", "[perft]")
{
	initmagicmoves();

	SECTION("Perft 0")
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(1) == 46);
	}

	SECTION("Perft 2")
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(2) == 2079);
	}

	SECTION("Perft 3")
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(3) == 89890);
	}

	/*SECTION("Perft 4") working but slow for unit test
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(4) == 3894594);
	}*/
}
