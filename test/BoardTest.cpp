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
