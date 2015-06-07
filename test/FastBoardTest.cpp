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

TEST_CASE( "Perft position 2 (Kiwipete)", "[perft]")
{
	initmagicmoves();
    FastBoard board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");

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
	/*
	SECTION("Perft 5") //working but slow for unit test
	{
		FastBoard board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
		REQUIRE(board.perft(5) == 674624);
	}*/
}

TEST_CASE( "Perft position 4 ", "[perft]")
{
	initmagicmoves();
	FastBoard board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	FastBoard boardMirrored("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");


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
	initmagicmoves();
    FastBoard board("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");

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
	initmagicmoves();
    FastBoard board("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

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
    /*
	SECTION("Perft 4") //working but slow for unit test
	{
		FastBoard board("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		REQUIRE(board.perft(4) == 3894594);
	}*/
}

TEST_CASE( "Perft Promotion", "[perft]") //Taken from http://www.rocechess.ch/perft.html
{
	initmagicmoves();
    FastBoard board("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1");

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
