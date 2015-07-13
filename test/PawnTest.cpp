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
        Board board("rnbqkbnr/ppppppp1/p7/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        REQUIRE(Pawn::countPawnsInFile(board,0,BLACK)==2);
        REQUIRE(Pawn::countPawnsInFile(board,3,BLACK)==1);
        REQUIRE(Pawn::countPawnsInFile(board,7,BLACK)==0);
        REQUIRE(Pawn::countPawns(board,BLACK)==8);
    }
}
