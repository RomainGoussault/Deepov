#include "catch.hpp"
#include "Board.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"


TEST_CASE( "is bit Set method" )
{
	//whitePawnStartingPosition
	U64 whitePawns(0LL | 0xFFLL << 8 );

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
    sp->updateAtkFr();
	REQUIRE(sp->getAtkFr(SQ_C5) == 0LL);
	REQUIRE(popcount(sp->getAtkFr(SQ_B1)) == 2);//Knight
	REQUIRE(popcount(sp->getAtkFr(SQ_C1)) == 0);//Bishop
	REQUIRE(popcount(sp->getAtkFr(SQ_A1)) == 0);//Rook
	REQUIRE(popcount(sp->getAtkFr(SQ_D1)) == 0);//Queen
	REQUIRE(popcount(sp->getAtkFr(SQ_E1)) == 0);//King

	REQUIRE(popcount(sp->getAtkFr(SQ_A2)) == 1); //Pawn
	REQUIRE(popcount(sp->getAtkFr(SQ_B2)) == 2); //Pawn

	REQUIRE(popcount(sp->getAtkFr(SQ_C7)) == 2); //Black Pawn

	sp = std::shared_ptr<Board>(new Board("r1b1k2r/p1pQ1p1p/np2pn2/4b2K/8/P1P3q1/4NPPP/3R1pNR w kq -"));
    sp->updateAtkFr();
	REQUIRE(popcount(sp->getAtkFr(SQ_E5)) == 4); //Bishop
	REQUIRE(popcount(sp->getAtkFr(SQ_D1)) == 10); //Rook
	REQUIRE(popcount(sp->getAtkFr(SQ_D7)) == 15); //Queen
	REQUIRE(popcount(sp->getAtkFr(SQ_E8)) == 4); //King
}


TEST_CASE( "EP squares" )
{
	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("rnbqkb1r/pp1ppppp/5n2/2pP4/8/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 3"));
    REQUIRE(sp->getLastEpSquare() == SQ_C6);
}
