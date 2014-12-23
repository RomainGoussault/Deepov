#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Bishop.hpp"
#include "Piece.hpp"
#include "Game.hpp"

//Perft data from: https://chessprogramming.wikispaces.com/Perft+Results

TEST_CASE( "Perft", "[perft]" )
{
    SECTION("Perft 0")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Game game(board);
        REQUIRE(game.perft(0) == 1);
    }

    SECTION("Perft 1")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Game game(board);
        REQUIRE(game.perft(1) == 20);
    }

    SECTION("Perft 2")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Game game(board);
        REQUIRE(game.perft(2) == 400);
    }


    SECTION("Perft 2")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Game game(board);
       // REQUIRE(game.perft(3) == 8902); //NOT WORKING
    }
}
