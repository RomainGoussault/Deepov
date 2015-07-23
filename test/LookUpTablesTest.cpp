#include "catch.hpp"
#include "LookUpTables.hpp"
#include "Color.hpp"

TEST_CASE( "LookUpTables" )
{
    SECTION("Bitboard calculations")
    {
        LookUpTables::init();
        int posIndex = 10;
        U64 frontMask=LookUpTables::frontBB(posIndex,WHITE);
        REQUIRE(frontMask == 0x404040404040000);

        frontMask=LookUpTables::frontBB(posIndex,BLACK);
        REQUIRE(frontMask == 0x4);
    }

    SECTION("Front spans")
    {
        LookUpTables::init();
        REQUIRE(LookUpTables::PASSED_PAWN_MASK[WHITE][34] == 0xe0e0e0000000000);
        REQUIRE(LookUpTables::PASSED_PAWN_MASK[BLACK][34] == 0xe0e0e0e);
        REQUIRE(LookUpTables::FRONT_SPANS[WHITE][34] == 0x404040000000000);
        REQUIRE(LookUpTables::FRONT_SPANS[BLACK][34] == 0x4040404);
        REQUIRE(LookUpTables::PASSED_PAWN_MASK[BLACK][44] == 0x3838383838);
    }
}
