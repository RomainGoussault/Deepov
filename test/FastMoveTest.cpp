#include "catch.hpp"
#include "FastMove.hpp"
#include "MagicMoves.hpp"


TEST_CASE( "Constructor and methods" )
{
    unsigned int origin = 4;
    unsigned int destination = 5;
    unsigned int flags = 6;
    FastMove move(origin, destination, flags);

    REQUIRE(move.getOrigin() == origin);
    REQUIRE(move.getDestination() == destination);
    REQUIRE(move.getFlags() == flags);

    move.setDestination(3);
    move.setOrigin(22);
    move.setFlags(0b1000);

    REQUIRE(move.getOrigin() == 22);
    REQUIRE(move.getDestination() == 3);
    REQUIRE(move.getFlags() == 8);
}

TEST_CASE( "is capture" )
{
	initmagicmoves();

	FastBoard board("8/8/3k4/8/8/8/n4K2/rR6 b - -");

	FastMove move = board.getRookPseudoLegalMoves(BLACK)[0];
    REQUIRE(move.isCapture() == true);

	move = board.getKnightPseudoLegalMoves(BLACK)[0];
    REQUIRE(move.isCapture() == false);
}
