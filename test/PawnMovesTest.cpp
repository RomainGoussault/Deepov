#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Pawn moves", "[pawn]" )
{
	SECTION("starting position")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 8*2);
		REQUIRE(blackSize == 8*2);
	}

	SECTION("4 moves test")
	{
		FastBoard board("8/8/8/8/8/2q1r3/3P4/8 w - -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 4);
	}
	
	SECTION("blocked pawns")
	{
		FastBoard board("8/8/1p2p3/qqq1r3/8/8/3P4/1q6 w - -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 2);
		REQUIRE(blackSize == 0);
	}
}
