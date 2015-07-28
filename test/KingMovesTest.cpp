#include "catch.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "MagicMoves.hpp"
#include <bitset>


TEST_CASE( "King moves", "[king]" )
{
    Tables::init();

	SECTION("Test pseudo-legal moves")
	{
		Board board("rnbq1b1r/ppp1np1p/4p1p1/3p2k1/3P2P1/8/PPPKPP1P/RNBQ1BNR w kq -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 7);
	}
}

TEST_CASE( "KingCastling1", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("Test Castling 1")
	{
		Board board("1nbqk2r/pppp1ppp/8/2p1bn2/5N2/1B1Q4/P1rPPPPP/R3K2R w KQkq -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 3);
		REQUIRE(blackSize == 3);
	}

	SECTION("Test Castling 2")
	{
		Board board("r3k2r/pppp1ppp/8/4b1n1/1n1NQbN1/3BB3/PPPPPPPP/R3K2R w k -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(blackSize == 4);
		REQUIRE(whiteSize == 2);
	}
}

TEST_CASE( "CastlingRights", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	Board board("r3k2r/8/8/8/3B4/8/8/R3K2R w KQkq - 0 1");


	SECTION("Test 1 Castling")
	{
		MoveGen moveGen(board);
		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 7);
		REQUIRE(blackSize == 7);
	}

	SECTION("Test 2 King move")
	{
		Move whiteKingMove(4,5,0,Piece::KING);
		board.executeMove(whiteKingMove);
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 0);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 0);
		board.undoMove(whiteKingMove);
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
	}

	SECTION("Test 3 Rook Move")
	{
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		Move whiteRookMove(0,16,0,Piece::ROOK);
		board.executeMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 0);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		board.undoMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}

	SECTION("Test 3 Rook Move2")
	{
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		Move whiteRookMove(07,23,0,Piece::ROOK);
		board.executeMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == true);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == false);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		board.undoMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}

	SECTION("Test 4 Rook Capture")
	{
		Move captureMove(27,63,Move::CAPTURE_FLAG,Piece::BISHOP);
		captureMove.setCapturedPieceType(Piece::ROOK);

		board.executeMove(captureMove);

		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 0);

		board.undoMove(captureMove);

		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}
}
