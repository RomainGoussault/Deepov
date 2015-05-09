#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"


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
    board.printBitBoard(board.getAllPieces());

    std::vector<FastMove> moveList = board.getWhitePawnPseudoLegalMoves();
    REQUIRE(moveList.size()==16);

    moveList=board.getKingPseudoLegalMoves(WHITE);
    REQUIRE(moveList.size()==0);

    moveList=board.getKnightPseudoLegalMoves(WHITE);
    REQUIRE(moveList.size()==4);
}

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
		//REQUIRE(board.perft(4) == 197 281);
	}
}
