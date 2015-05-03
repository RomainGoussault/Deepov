#include "catch.hpp"
#include "FastBoard.hpp"

TEST_CASE( "Knight moves", "[knight]" )
{
	SECTION("Test pseudo-legal moves")
	{
		FastBoard board("8/4kB2/8/5b2/8/1bqKN3/8/n7 w - -");
		int whiteSize = board.getKnightPseudoLegalMoves(WHITE).size();
		int blackSize = board.getKnightPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 8);
		REQUIRE(blackSize == 1);
	}
}
