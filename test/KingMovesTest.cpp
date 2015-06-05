#include "catch.hpp"
#include "FastBoard.hpp"
#include "MoveGen.hpp"


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
	SECTION("Test Castling 2 ")
	{
		FastBoard board("1nbqk2r/pppp1ppp/8/2p1bn2/5N2/1B1Q4/P1rPPPPP/R3K2R w KQkq -");
		MoveGen moveGen(board);

		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 3);
		REQUIRE(blackSize == 3);
	}
}

TEST_CASE( "KingCastling2", "[king]" )
{
	SECTION("gfdgfdgfdg")
	{
		FastBoard board("r3k2r/pppp1ppp/8/4bNn1/1nQN1b2/3BB3/PPPPPPPP/R3K2R w k -");
		MoveGen moveGen(board);

		int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		REQUIRE(blackSize == 4);
		REQUIRE(whiteSize == 2);
	}
}
