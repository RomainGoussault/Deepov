#include "catch.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Pawn moves", "[pawn]" )
{
    Tables::init();

	SECTION("starting position")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		unsigned int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 8*2);
		REQUIRE(blackSize == 8*2);
	}

	SECTION("4 moves test")
	{
		Board board("8/8/8/8/8/2q1r3/3P4/8 w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 4);
	}

	SECTION("blocked pawns")
	{
		Board board("8/8/1p2p3/qqq1r3/8/8/3P4/1q6 w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		unsigned int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 2);
		REQUIRE(blackSize == 0);
	}
}

TEST_CASE( "Pawn promotions", "[pawn]" )
{
    Tables::init();

    SECTION("Promotion")
	{
		Board board("8/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 4);
	}

	SECTION("Promotion with capture")
	{
		Board board("1r6/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
		MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 8);

        U64 pawnBitboard = board.getWhitePawns();

        Move promotionCapture(static_cast<Square>(50),static_cast<Square>(57),Move::PROMOTION_FLAG + Move::CAPTURE_FLAG, Piece::PAWN);
		promotionCapture.setCapturedPieceType(Piece::ROOK);

		board.executeMove(promotionCapture);
		REQUIRE(pawnBitboard != board.getWhitePawns());

		board.undoMove(promotionCapture);
		REQUIRE(pawnBitboard == board.getWhitePawns());
	}

	SECTION("Promotion with double capture")
	{
		Board board("3r1r2/4P3/8/k7/8/8/8/1K6 w - - 0 1");
		MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 12);
	}
}
