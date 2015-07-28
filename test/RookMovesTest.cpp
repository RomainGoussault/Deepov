#include "catch.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Rook moves", "[rook]" )
{
	MagicMoves::initmagicmoves();
    Tables::init();
	SECTION("Test pseudo-legal moves")
	{
		Board board("1bq1b2p/p2p1pp1/2Bk4/1N6/4r1Q1/B6P/PP1PPPPR/3K2R1 b K -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getRookPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getRookPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 11);
	}
}
