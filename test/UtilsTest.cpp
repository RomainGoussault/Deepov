/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "catch.hpp"
#include "Utils.hpp"
#include "BitBoardUtils.hpp"

TEST_CASE( "Conversion string to unsigned int" )
{
    unsigned int convertedString ;
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
        REQUIRE(popcount(testInt)==3);

        testInt=0x18060600045ead;
        REQUIRE(popcount(testInt)==17);

        testInt=0x0;
        REQUIRE(popcount(testInt)==0);
    }
}

TEST_CASE("getFile")
{
    REQUIRE(Utils::getFile(SQ_B1)==1);
    REQUIRE(Utils::getFile(static_cast<Square>(32))==0);
    REQUIRE(Utils::getFile(static_cast<Square>(46))==6);
}
