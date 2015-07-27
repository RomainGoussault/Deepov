#include "catch.hpp"
#include "Tables.hpp"
#include "Color.hpp"

TEST_CASE( "Tables" )
{
    SECTION("Bitboard calculations")
    {
        Tables::init();
        unsigned int posIndex = 10;
        U64 frontMask=Tables::frontBB(posIndex,WHITE);
        REQUIRE(frontMask == 0x404040404040000);

        frontMask=Tables::frontBB(posIndex,BLACK);
        REQUIRE(frontMask == 0x4);
    }

    SECTION("Front spans")
    {
        Tables::init();
        REQUIRE(Tables::PASSED_PAWN_MASK[WHITE][34] == 0xe0e0e0000000000);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][34] == 0xe0e0e0e);
        REQUIRE(Tables::FRONT_SPANS[WHITE][34] == 0x404040000000000);
        REQUIRE(Tables::FRONT_SPANS[BLACK][34] == 0x4040404);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][44] == 0x3838383838);
    }
}
