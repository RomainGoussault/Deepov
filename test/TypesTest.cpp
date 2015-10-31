#include "catch.hpp"
#include "Tables.hpp"
#include "Types.hpp"

TEST_CASE( "Types" )
{
    Tables::init();

    SECTION("getLine")
    {
        REQUIRE(getLine(SQ_A1) == 0);
        REQUIRE(getLine(SQ_C7) == 2);
    }

    SECTION("getRank")
    {
        REQUIRE(getRank(SQ_A1) == 0);
        REQUIRE(getRank(SQ_C7) == 6);
    }
}
