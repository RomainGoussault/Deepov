#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "isCheck" )
{
	FastBoard fb = FastBoard("8/8/k7/2N5/8/8/4K3/1n6 w - -");
	REQUIRE(fb.isCheck(BLACK) == true);
	REQUIRE(fb.isCheck(WHITE) == false);
}

