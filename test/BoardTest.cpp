#include "catch.hpp"
#include "Board.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"


TEST_CASE( "is bit Set method" )
{
	//whitePawnStartingPosition
	U64 whitePawns(0 | 0xFF << 8 );

	REQUIRE(BitBoardUtils::isBitSet(0, 5, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 0, 0) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 0) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 7, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 1, 5) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 5, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 0, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 7, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 1) == true);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 2) == false);
	REQUIRE(BitBoardUtils::isBitSet(whitePawns, 2, 7) == false);
}

TEST_CASE( "AtkFr" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board());

	REQUIRE(sp->getAtkFr(SQ_C5) == 0);
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_B1)) == 3);//Knight
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_C1)) == 2);//Bishop
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_A1)) == 2);//Rook

	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_A2)) == 1); //Pawn
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_B2)) == 2); //Pawn

	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_C7)) == 2); //Black Pawn

	sp = std::shared_ptr<Board>(new Board("r1b1k2r/p1pp1p1p/np2pn2/4b2K/8/P1P3q1/4NPPP/3R1pNR w KQkq -"));
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_E5)) == 7); //Bishop
	REQUIRE(BitBoardUtils::countBBBitsSet(sp->getAtkFr(SQ_D1)) == 11); //Rook
}
