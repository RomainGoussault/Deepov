#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"
#include "MagicMoves.hpp"
#include <bitset>


TEST_CASE( "King moves", "[king]" )
{
	SECTION("Test pseudo-legal moves")
	{
		FastBoard board("rnbq1b1r/ppp1np1p/4p1p1/3p2k1/3P2P1/8/PPPKPP1P/RNBQ1BNR w kq -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 7);
	}
}

TEST_CASE( "KingCastling1", "[king]" )
{
	initmagicmoves();

	SECTION("Test Castling 1")
	{
		FastBoard board("1nbqk2r/pppp1ppp/8/2p1bn2/5N2/1B1Q4/P1rPPPPP/R3K2R w KQkq -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 3);
		REQUIRE(blackSize == 3);
	}

	SECTION("Test Castling 2")
	{
		FastBoard board("r3k2r/pppp1ppp/8/4b1n1/1n1NQbN1/3BB3/PPPPPPPP/R3K2R w k -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(blackSize == 4);
		REQUIRE(whiteSize == 2);
	}
}

TEST_CASE( "CastlingRights", "[king]" )
{
    initmagicmoves();
    FastBoard board("r3k2r/8/8/8/3B4/8/8/R3K2R w KQkq - 0 1");


	SECTION("Test 1 Castling")
	{
        MoveGen moveGen(board);
		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 7);
		REQUIRE(blackSize == 7);
    }

    SECTION("Test 2 King move")
	{
        FastMove whiteKingMove(4,5,0,FastMove::KING_TYPE);
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
        FastMove whiteRookMove(0,16,0,FastMove::ROOK_TYPE);
        board.executeMove(whiteRookMove);
        board.updateCastlingRights(whiteRookMove);
        int origin = whiteRookMove.getOrigin();
        int isOnInitialPos = (1LL << origin)&LookUpTables::ROOK_INITIAL_POS;
        unsigned int shift(((~origin)&0b0001) + 2*((origin&0b1000)>>3));
        unsigned int mask = ~(0b0001 << shift);
        std::cout << origin << std::endl;
        std::cout << isOnInitialPos << std::endl;
        std::cout << shift << std::endl;
        std::cout << std::bitset<16>(mask) << std::endl;
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

    SECTION("Test 4 Rook Capture")
	{
        FastMove captureMove(27,63,FastMove::CAPTURE_FLAG,FastMove::BISHOP_TYPE);
        captureMove.setCapturedPieceType(FastMove::ROOK_TYPE);
        board.executeMove(captureMove);
        REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
        REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 0);
        board.undoMove(captureMove);
        REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
        REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
    }
}
