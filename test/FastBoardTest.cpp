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

	SECTION("Perft 0")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(1) == 20);
	}

	SECTION("Perft 2")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(2) == 400);
	}

	SECTION("Perft 3")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(3) == 8902);
	}

	SECTION("Perft 4")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(4) == 197281);
	}

	SECTION("Perft 5")
	{
		initmagicmoves();

		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		//REQUIRE(board.perft(5) == 4865609);
	}
}
