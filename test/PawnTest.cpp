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

    SECTION("Isolated/Passed Pawns")
    {
        Board board("4k3/p1p4p/p3pP2/7P/2pP2p1/1P6/P4PP1/4K3 b KQkq - 0 1");
        REQUIRE(Pawn::countPawnsInFile(board,2,BLACK)==2);
        REQUIRE(Pawn::countPawnsInFile(board,5,WHITE)==2);
        REQUIRE(Pawn::hasNeighbors(board,3,WHITE)==false);
        REQUIRE(Pawn::hasNeighbors(board,5,WHITE)==true);
        REQUIRE(Pawn::hasNeighbors(board,4,BLACK)==false);
        REQUIRE(Pawn::hasNeighbors(board,3,BLACK)==true);
        REQUIRE(Pawn::initDoubledPawns(board)==-Pawn::DOUBLED_PAWN_PENALTY);
        REQUIRE(Pawn::initPassedPawns(board)==Pawn::PASSED_PAWN_BONUS);
        REQUIRE(Pawn::initIsolatedPawns(board)==-2*Pawn::ISOLATED_PAWN_PENALTY);
    }
}
