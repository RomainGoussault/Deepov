#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "knight check" )
{
	FastBoard fb = FastBoard("8/8/k7/2N5/8/8/4K3/1n6 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "rook check" )
{
	initmagicmoves();

	FastBoard fb = FastBoard("7n/8/k2R4/3r4/8/8/4K3/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "bishop check" )
{
	initmagicmoves();

	FastBoard fb = FastBoard("2B3Rn/1r6/k7/8/2b5/8/4K3/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == false);
	REQUIRE(fb.isCheck(WHITE) == true);
}

TEST_CASE( "queen check" )
{
	initmagicmoves();

	FastBoard fb = FastBoard("6q1/6q1/6q1/6q1/8/2k2K2/8/Q7 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

TEST_CASE( "king check" )
{
	FastBoard fb = FastBoard("8/8/1k6/8/8/3K4/8/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == false);
	REQUIRE(fb.isCheck(WHITE) == false);

	fb = FastBoard("8/8/8/8/2k5/3K4/8/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == true);
}


