#include "catch.hpp"
#include "Utils.hpp"

TEST_CASE( "Conversion string to int" )
{
    int convertedString ;
    std::string aString = "3";
    convertedString = Utils::convertStringToInt(aString) ;
    REQUIRE( convertedString == 3);

    aString = "34";
    convertedString = Utils::convertStringToInt(aString) ;
    REQUIRE( convertedString == 34);

    aString = "102";
    convertedString = Utils::convertStringToInt(aString) ;
    REQUIRE( convertedString == 102);
}

TEST_CASE("Bit manipulation")
{
    SECTION("Count set bits")
    {
        U64 testInt(0x810001000);
        REQUIRE(Utils::countBBBitsSet(testInt)==3);

        testInt=0x18060600045ead;
        REQUIRE(Utils::countBBBitsSet(testInt)==17);

        testInt=0x0;
        REQUIRE(Utils::countBBBitsSet(testInt)==0);
    }
}


