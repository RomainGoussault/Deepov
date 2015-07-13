#include "catch.hpp"
#include "Pawn.hpp"
#include "Board.hpp"


TEST_CASE("Pawn structure")
{

	SECTION("Initial Position")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        REQUIRE(Pawn::initDoubledPawns(board) == 0);
        REQUIRE(Pawn::countPawns(board,WHITE)==8);
    }

	SECTION("Doubled Pawns")
	{
        Board board("rnbqkbnr/pppppppp/p7/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        REQUIRE(Pawn::isDoubledPawns(board,0,BLACK)==true);
        REQUIRE(Pawn::isDoubledPawns(board,3,BLACK)==false);
        REQUIRE(Pawn::countPawns(board,BLACK)==9);
    }
}
