#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Knight.hpp"
#include "Piece.hpp"

TEST_CASE( "Knight possible moves", "[Knight]" )
{

	SECTION("Knight on starting rank")
    {
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1");
		Position position(1,0);
		PiecePtr knightPtr = board.getPiecePtr(position);
		int size = knightPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 2);
    }

	SECTION("Knight free")
	{
		Board board("8/4k3/8/3K4/4N3/8/8/8 w - - 0 1");
		Position position(4,3);
		PiecePtr knightPtr = board.getPiecePtr(position);

		int size = knightPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 8);
	}

	SECTION("Knight blocked by allied pieces")
	{
		Board board("8/4k3/3R1R2/2B3B1/4N3/2P3P1/3Q1P2/3K4 w - - 0 1");
		Position position(4,3);
		PiecePtr knightPtr = board.getPiecePtr(position);

		int size = knightPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 0);
	}

	SECTION("Knight blocked by enemy pieces")
	{
		Board board("n7/8/4K3/8/5N2/8/4k3/8 b - - 0 1");
		Position blackPosition(0,7);
		Position whitePosition(5,3);

		PiecePtr blackBishopPtr = board.getPiecePtr(blackPosition);
		PiecePtr whiteBishopPtr = board.getPiecePtr(whitePosition);

		int blackSize = blackBishopPtr->getAttackedPositions(board).size();
		int whiteSize = whiteBishopPtr->getAttackedPositions(board).size();

		REQUIRE(blackSize == 2);
		REQUIRE(whiteSize == 8);
	}
}
