#include "catch.hpp"
#include "FastBoard.hpp"


TEST_CASE( "is bit Set method" )
{
	//whitePawnStartingPosition
	U64 whitePawns(0 | 0xFF << 8 );

    REQUIRE(FastBoard::isBitSet(0, 5, 5) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 0, 0) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 5, 0) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 5, 5) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 7, 5) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 1, 5) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 5, 1) == true);
    REQUIRE(FastBoard::isBitSet(whitePawns, 0, 1) == true);
    REQUIRE(FastBoard::isBitSet(whitePawns, 7, 1) == true);
    REQUIRE(FastBoard::isBitSet(whitePawns, 2, 1) == true);
    REQUIRE(FastBoard::isBitSet(whitePawns, 2, 2) == false);
    REQUIRE(FastBoard::isBitSet(whitePawns, 2, 7) == false);
}


TEST_CASE( "Move methods" )
{
    FastBoard board;
    board.printBitBoard(board.getAllPieces());

    std::vector<FastMove> moveList = board.whitePawnPseudoLegalMoves();
    REQUIRE(moveList.size()==16);

    moveList=board.getKingPseudoLegalMoves(WHITE);
    REQUIRE(moveList.size()==0);

    moveList=board.getKnightPseudoLegalMoves(WHITE);
    REQUIRE(moveList.size()==4);
}
