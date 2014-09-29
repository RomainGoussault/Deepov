#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"

TEST_CASE( "is position on Board test", "[factorial]" )
{
    Board board;
    Position position(3, 4);
    REQUIRE(board.isPositionOnBoard(position));
}
