#include "catch.hpp"
#include "FastBoard.hpp"

TEST_CASE( "Pawn moves", "[pawn]" )
{
	SECTION("Test pseudo-legal moves starting position")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		int whiteSize = board.whitePawnPseudoLegalMoves().size();
		int blackSize = board.blackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 8*2);
		REQUIRE(blackSize == 8*2);
	}
}
