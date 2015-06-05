#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Pawn moves", "[pawn]" )
{
	SECTION("starting position")
	{
		FastBoard board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 8*2);
		REQUIRE(blackSize == 8*2);
	}

	SECTION("4 moves test")
	{
		FastBoard board("8/8/8/8/8/2q1r3/3P4/8 w - -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 4);
	}

	SECTION("blocked pawns")
	{
		FastBoard board("8/8/1p2p3/qqq1r3/8/8/3P4/1q6 w - -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 2);
		REQUIRE(blackSize == 0);
	}
}

TEST_CASE( "Pawn promotions", "[pawn]" )
{
    SECTION("Promotion")
	{
		FastBoard board("8/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        MoveGen moveGen(board);
		int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 4);
	}

	SECTION("Promotion with capture")
	{
		FastBoard board("1r6/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
		MoveGen moveGen(board);
		int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 8);

        U64 pawnBitboard = board.getWhitePawns();

        FastMove promotionCapture(50,57,FastMove::PROMOTION_FLAG + FastMove::CAPTURE_FLAG, FastMove::PAWN_TYPE);
		promotionCapture.setCapturedPieceType(FastMove::ROOK_TYPE);

		board.executeMove(promotionCapture);
		REQUIRE(pawnBitboard != board.getWhitePawns());

		board.undoMove(promotionCapture);
		REQUIRE(pawnBitboard == board.getWhitePawns());
	}

	SECTION("Promotion with double capture")
	{
		FastBoard board("3r1r2/4P3/8/k7/8/8/8/1K6 w - - 0 1");
		MoveGen moveGen(board);
		int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 12);
	}
}
