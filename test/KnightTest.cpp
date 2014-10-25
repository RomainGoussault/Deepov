#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Knight.hpp"
#include "Piece.hpp"

TEST_CASE( "Knight possible moves ", "[Knight]" )
{
	SECTION("Knight blocked by ennemy pieces")
	{
		Board board("8/2r1r3/8/3K4/5b2/8/8/8 w - - 0 1");
		Position position(4,4);
		PiecePtr KnightPtr = board.getPiecePtr(position);

	    int size = KnightPtr->getPseudoLegalMoves(board).size();
	    REQUIRE(size == 5);
	}


}

