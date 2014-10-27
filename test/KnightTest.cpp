#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Knight.hpp"
#include "Piece.hpp"

TEST_CASE( "Knight possible moves ", "[Knight]" )
{
	SECTION("Knight free")
	{
		Board board("8/4k3/8/3K4/4N3/8/8/8 w - - 0 1");
		Position position(4,3);
		PiecePtr KnightPtr = board.getPiecePtr(position);

	    int size = KnightPtr->getPseudoLegalMoves(board).size();
	    REQUIRE(size == 8);
	}
}

