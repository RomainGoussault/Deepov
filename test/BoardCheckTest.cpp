#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "knight check" )
{
	Board fb = Board("8/8/k7/2N5/8/8/4K3/1n6 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "rook check" )
{
	MagicMoves::initmagicmoves();

	Board fb = Board("7n/8/k2R4/3r4/8/8/4K3/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "bishop check" )
{
	MagicMoves::initmagicmoves();

	Board fb = Board("2B3Rn/1r6/k7/8/2b5/8/4K3/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == false);
	REQUIRE(fb.isCheck(WHITE) == true);
}

TEST_CASE( "queen check" )
{
	MagicMoves::initmagicmoves();

	Board fb = Board("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "king check" )
{
	Board fb = Board("8/8/1k6/8/8/3K4/8/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == false);
	REQUIRE(fb.isCheck(WHITE) == false);

	fb = Board("8/8/8/8/2k5/3K4/8/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == true);
}

TEST_CASE( "pawn check" )
{
	Board fb = Board("8/8/8/8/2k2p2/6K1/2P5/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == false);
	REQUIRE(fb.isCheck(WHITE) == true);

	fb = Board("2k5/3P3p/6K1/8/8/8/8/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == true);
}

