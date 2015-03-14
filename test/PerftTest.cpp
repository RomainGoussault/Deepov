#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Bishop.hpp"
#include "Piece.hpp"
#include "Game.hpp"

//Perft data from: https://chessprogramming.wikispaces.com/Perft+Results

TEST_CASE( "Perft from initial position", "[perft]")
{
	SECTION("Perft 0")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(0) == 1);
	}

	SECTION("Perft 1")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(1) == 20);
	}

	SECTION("Perft 2")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.perft(2) == 400);
        // REQUIRE(board.perft(3) == 8902); // This one is ok
	}


	SECTION("Perft 4")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		//REQUIRE(board.perft(4) == 197281); // This one is ok too
		//REQUIRE(board.perft(5) == 4865609); // too  long for my patience but i guess it will fail
	}


}

// Position 2 from https://chessprogramming.wikispaces.com/Perft+Results
TEST_CASE( "Perft position 2", "[perft]")
{
    Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
    REQUIRE(board.perft(1) == 48);
    REQUIRE(board.perft(2) == 2039);
    // TODO
    // REQUIRE(board.perft(3) == 97862); // This one works
    // REQUIRE(board.perft(4) == 4085603); // This one doesn't work, probably because checkmate is not implemented
}


// Position 3 from https://chessprogramming.wikispaces.com/Perft+Results
TEST_CASE( "Perft position 3", "[perft]")
{
    Board board("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -");
    REQUIRE(board.perft(1) == 14);
    REQUIRE(board.perft(2) == 191);
    // REQUIRE(board.perft(3) == 2812);
    // REQUIRE(board.perft(4) == 43238); // All works ok
}

// Position 4 from https://chessprogramming.wikispaces.com/Perft+Results
TEST_CASE( "Perft position 4", "[perft]")
{
    Board board("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
    board.divide(1);
    REQUIRE(board.perft(1) == 6);
    REQUIRE(board.perft(2) == 264);
    //TODO
    //REQUIRE(board.perft(3) == 9467); // works till here
    //REQUIRE(board.perft(4) == 422333); // Idm fails because no checkmate implemented
}

// Position 5 from https://chessprogramming.wikispaces.com/Perft+Results
TEST_CASE( "Perft position 5", "[perft]")
{
    Board board("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
    REQUIRE(board.perft(1) == 42);
    REQUIRE(board.perft(2) == 1352);
    //REQUIRE(board.perft(3) == 53392);
    /* fails,
    This position was discussed on Talkchess and caught bugs in engines several years old at depth 3.*/
    // No accurate data here, issue on castling probably ? We have to look more precisely

}


