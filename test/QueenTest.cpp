#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Queen.hpp"
#include "Piece.hpp"

TEST_CASE( "Queen possible moves ", "[queen]" )
{
	SECTION("Queen surrounded by enemy pieces")
	{
		Board board("8/2k5/2brb3/2rQr3/2rbq1K1/8/8/8 w - - 0 1");
		Position position(3,4);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 8);
	}

	SECTION("Queen blocked by allied pieces")
	{
		Board board("8/8/8/8/8/5k2/RB6/QK6 w - - 0 1 w - - 0 1");
		Position position(0,0);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 0);
	}

	SECTION("Queen bishop mode")
	{
		Board board("5k2/8/3r4/2rqr3/3r4/8/4K3/8 w - - 0 1");
		Position position(3,4);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 13);
	}

	SECTION("Queen rook mode")
	{
		Board board("5k2/8/2r1r3/3q4/2r1r3/8/4K3/8 w - - 0 1");
		Position position(3,4);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 14);
	}

	SECTION("Queen free")
	{
		Board board("5k2/8/8/3q4/8/8/4K3/8 w - - 0 1");
		Position position(3,4);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 27);
	}

	SECTION("Queen random test")
	{
		Board board("8/5K2/5Q2/4b3/7r/8/7k/8 w - - 0 1");
		Position position(5,5);
		PiecePtr queenPtr = board.getPiecePtr(position);

		int size = queenPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 19);
	}

	SECTION("Queen attacked positions")
	{
		Board board("Q7/8/4K3/8/6q1/8/4k3/8 w - - 0 1");
		Position blackPosition(6,3);
		Position whitePosition(0,7);

		PiecePtr blackBishopPtr = board.getPiecePtr(blackPosition);
		PiecePtr whiteBishopPtr = board.getPiecePtr(whitePosition);

		int blackSize = blackBishopPtr->getAttackedPositions(board).size();
		int whiteSize = whiteBishopPtr->getAttackedPositions(board).size();

		REQUIRE(blackSize == 7+7+1+1+2+2);
		REQUIRE(whiteSize == 7+7+7);
	}
}
