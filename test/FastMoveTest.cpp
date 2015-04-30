#include "catch.hpp"
#include "FastMove.hpp"


TEST_CASE( "Constructor and getter methods" )
{
    unsigned int origin = 4;
    unsigned int destination = 5;
    unsigned int flags = 6;
    FastMove move(origin, destination, flags);

    REQUIRE(move.getOrigin() == origin);
    REQUIRE(move.getDestination() == destination);
    REQUIRE(move.getFlags() == flags);
}
