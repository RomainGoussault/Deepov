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
