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
	FastBoard fb = FastBoard("7n/8/k2R4/3r4/8/8/4K3/8 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

