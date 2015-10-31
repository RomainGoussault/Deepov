#include "catch.hpp"
#include "Tables.hpp"
#include "Types.hpp"

TEST_CASE( "Types" )
{
    Tables::init();

    SECTION("getFile")
    {
        REQUIRE(getFile(SQ_A1) == 0);
        REQUIRE(getFile(SQ_C7) == 2);
    }

    SECTION("getRank")
    {
        REQUIRE(getRank(SQ_A1) == 0);
        REQUIRE(getRank(SQ_C7) == 6);
    }
}
