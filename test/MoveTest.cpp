#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Color.hpp"
#include "Move.hpp"


TEST_CASE( "Constructor" )
{
    Position origin(0,0);
    Position destination(2,2);
    Move testMove(origin,destination);

    REQUIRE(testMove.isCastling()==false);
    REQUIRE(testMove.getCancelledCastling(0)==false);
    REQUIRE(testMove.getCancelledCastling(1)==false);
}
