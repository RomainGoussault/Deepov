#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"


TEST_CASE( "King moves", "[king]" )
{
	SECTION("Test pseudo-legal moves")
	{
		FastBoard board("rnbq1b1r/ppp1np1p/4p1p1/3p2k1/3P2P1/8/PPPKPP1P/RNBQ1BNR w kq -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 7);
	}
}
