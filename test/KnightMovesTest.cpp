#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Knight moves", "[knight]" )
{
	SECTION("Test pseudo-legal moves with one knight")
	{
		FastBoard board("8/4kB2/8/5b2/8/1bqKN3/8/n7 w - -");
		MoveGen moveGen(&board);

		int whiteSize = moveGen.getKnightPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKnightPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 8);
		REQUIRE(blackSize == 1);
	}

	SECTION("Test pseudo-legal moves with 2 knights")
	{
		FastBoard board("8/1N6/3q4/8/3r4/3B4/8/7N w - -");
		MoveGen moveGen(&board);

		int whiteSize = moveGen.getKnightPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKnightPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 6);
		REQUIRE(blackSize == 0);
	}
}
