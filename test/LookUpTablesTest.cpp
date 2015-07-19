#include "catch.hpp"
#include "LookUpTables.hpp"
#include "Color.hpp"

TEST_CASE( "LookUpTables" )
{
    SECTION("Bitboard calculations")
    {
        int posIndex = 10;
        U64 frontMask=LookUpTables::frontBB(posIndex,WHITE);
        REQUIRE(frontMask == 0x404040404040000);

        frontMask=LookUpTables::frontBB(posIndex,BLACK);
        REQUIRE(frontMask == 0x4);
    }
}
