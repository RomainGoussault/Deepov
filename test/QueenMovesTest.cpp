#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"

TEST_CASE( "Queen moves", "[queen]" )
{
	initmagicmoves();

	SECTION("Test pseudo-legal moves")
	{
		FastBoard board("k1q1b2p/p2p1pp1/2B1Q3/1N3P2/4r3/2Pn1Q1P/P1RPP1PR/B1K3R1 b K -");
		int whiteSize = board.getQueenPseudoLegalMoves(WHITE).size();
		int blackSize = board.getQueenPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 6+3 + 8+5);
		REQUIRE(blackSize == 4+2);
	}
}
