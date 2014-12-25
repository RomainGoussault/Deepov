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
		        PiecePtr rook (new Rook(position, BLACK));
		        Board board;
		        board.addPiece(rook);
		        int size = rook->getPseudoLegalMoves(board).size();
		        REQUIRE(size == 14);
		    }
		}
	}

	SECTION("Rook blocked by allied pieces")
	{
		Position position(0, 0);
		Position position1(0, 1);
		Position position2(1, 0);

		PiecePtr rook(new Rook(position, BLACK));
		PiecePtr rook1(new Rook(position1, BLACK));
		PiecePtr rook2(new Rook(position2, BLACK));

        Board board;

        board.addPiece(rook);
        board.addPiece(rook1);
        board.addPiece(rook2);

	    int size = rook->getPseudoLegalMoves(board).size();
	    REQUIRE(size == 0);
	}

	SECTION("Rook blocked by enemy pieces")
	{
		Position position(0, 0);
		Position position1(0, 1);
		Position position2(1, 0);

		PiecePtr rook(new Rook(position, WHITE));
		PiecePtr rook1(new Rook(position1, BLACK));
		PiecePtr rook2(new Rook(position2, BLACK));

        Board board;

        board.addPiece(rook);
        board.addPiece(rook1);
        board.addPiece(rook2);

	    int size = rook->getPseudoLegalMoves(board).size();
	    REQUIRE(size == 2);
	}

    SECTION("Rook attacking squares")
    {
        Board board("8/3p4/5k2/3R4/8/3P4/2K5/8 w - - 0 1");
        Position position(3,4);
        PiecePtr rookPtr = board.getPiecePtr(position);
        int size = rookPtr->getAttackedPositions(board).size();
        REQUIRE(size == 11);
    }

    SECTION("Rook attacking squares, tight")
    {
        Board board("8/8/3p1k2/2KRn3/3P4/8/8/8 w - - 0 1");
        Position position(3,4);
        PiecePtr rookPtr = board.getPiecePtr(position);
        int size = rookPtr->getAttackedPositions(board).size();
        REQUIRE(size == 4);
    }

    SECTION("rook get legal moves")
	{
		Board board("7k/8/4r3/8/R7/4K3/8/8 w - - 0 1");
		Position position(0,3);
		PiecePtr rookPtr = board.getPiecePtr(position);
		REQUIRE(rookPtr->getLegalMoves(board).size() == 1);
	}
}
