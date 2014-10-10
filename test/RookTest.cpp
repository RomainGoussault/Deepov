#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Rook.hpp"
#include "Piece.hpp"

TEST_CASE( "Rook possible moves ", "[rook]" )
{

	SECTION("Rook alone on board")
	{	for(int i = 0; i < 8; ++i )
		{
		    for(int j = 0; j < 8; ++j )
		    {
		        Position position(i, j);
		        Rook rook(position, BLACK);
		        Board board;
		        board.addPiece(rook);
		        int size = rook.getPseudoLegalMoves(board).size();
		        REQUIRE(size == 14);
		    }
		}
	}

	SECTION("Rook blocked by allied pieces")
	{
		Position position(0, 0);
		Position position1(0, 1);
		Position position2(1, 0);

        Rook rook(position, BLACK);
        Rook rook1(position1, BLACK);
        Rook rook2(position2, BLACK);

        Board board;

        board.addPiece(rook);
        board.addPiece(rook1);
        board.addPiece(rook2);

	    int size = rook.getPseudoLegalMoves(board).size();
	    REQUIRE(size == 0);
	}

	SECTION("Rook blocked by ennemy pieces")
	{
		Position position(0, 0);
		Position position1(0, 1);
		Position position2(1, 0);

        Rook rook(position, WHITE);
        Rook rook1(position1, BLACK);
        Rook rook2(position2, BLACK);

        Board board;

        board.addPiece(rook);
        board.addPiece(rook1);
        board.addPiece(rook2);

	    int size = rook.getPseudoLegalMoves(board).size();
	    REQUIRE(size == 2);
	}
}
