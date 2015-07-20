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
        REQUIRE(LookUpTables::FRONT_SPANS[WHITE][34] == 0xe0e0e0000000000);
        REQUIRE(LookUpTables::FRONT_SPANS[BLACK][34] == 0xe0e0e0e);
        REQUIRE(LookUpTables::FRONT_SQUARES[WHITE][34] == 0x404040000000000);
        REQUIRE(LookUpTables::FRONT_SQUARES[BLACK][34] == 0x4040404);
    }
}
