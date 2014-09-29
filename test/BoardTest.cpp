#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"

TEST_CASE( "is position on Board test", "[board]" )
{
    Board board;
    Position position1(0, 0);
    Position position2(7,7);
    Position position3(6,4);

    Position position4(8,4);
    Position position5(4,8);
    Position position6(-1,4);
    Position position7(6,-1);

    REQUIRE(board.isPositionOnBoard(position1));
    REQUIRE(board.isPositionOnBoard(position2));
    REQUIRE(board.isPositionOnBoard(position3));

    REQUIRE_FALSE(board.isPositionOnBoard(position4));
    REQUIRE_FALSE(board.isPositionOnBoard(position5));
    REQUIRE_FALSE(board.isPositionOnBoard(position6));
    REQUIRE_FALSE(board.isPositionOnBoard(position7));
}
