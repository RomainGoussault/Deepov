#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Queen moves", "[queen]" )
{
	MagicMoves::initmagicmoves();
    Tables::init();
	SECTION("Test pseudo-legal moves")
	{
		Board board("k1q1b2p/p2p1pp1/2B1Q3/1N3P2/4r3/2Pn1Q1P/P1RPP1PR/B1K3R1 b K -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getQueenPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getQueenPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 6+3 + 8+5);
		REQUIRE(blackSize == 4+2);
	}
}
