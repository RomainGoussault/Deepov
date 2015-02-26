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


