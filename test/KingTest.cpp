#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "King.hpp"
#include "Piece.hpp"

TEST_CASE( "King moves ", "[king]" )
{
	SECTION("Random position 1")
	{
		Board board("rnbqkbnr/ppp2ppp/4p3/3p4/3P4/8/PPPKPPPP/RNBQ1BNR w kq - 0 3");
		Position position(3,1);
		PiecePtr kingPtr = board.getPiecePtr(position);

		int size = kingPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 4);
	}
}
