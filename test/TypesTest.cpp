#include "catch.hpp"
#include "Tables.hpp"
#include "Board.hpp"
#include "Types.hpp"

TEST_CASE( "Types" )
{
    Tables::init();

    SECTION("getFile")
    {
        REQUIRE(getFile(SQ_A1) == 0);
        REQUIRE(getFile(SQ_C7) == 2);
    }

    SECTION("getRank")
    {
        REQUIRE(getRank(SQ_A1) == 0);
        REQUIRE(getRank(SQ_C7) == 6);
    }
}

TEST_CASE( "Bitboard and Squares Operator overloading" )
{
    Tables::init();

    SECTION("AND")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        U64 b1 = wr & SQ_A1;
        REQUIRE(popcount(b1) == 1);

        U64 b2 = wr & SQ_A2;
        REQUIRE(popcount(b2) == 0);
    }

    SECTION("OR")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        U64 b1 = wr | SQ_A1;
        REQUIRE(popcount(b1) == 2);

        U64 b2 = wr | SQ_A2;
        REQUIRE(popcount(b2) == 3);
    }

    SECTION("XOR")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        U64 b1 = wr ^ SQ_A1;
        REQUIRE(popcount(b1) == 1);

        U64 b2 = wr ^ SQ_A2;
        REQUIRE(popcount(b2) == 3);
    }

    SECTION("=AND")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        wr &= SQ_A1;
        REQUIRE(popcount(wr) == 1);

        wr = board.getWhiteRooks();
        wr &= SQ_A2;
        REQUIRE(popcount(wr) == 0);
    }

    SECTION("=OR")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        wr |= SQ_A1;
        REQUIRE(popcount(wr) == 2);

        wr = board.getWhiteRooks();
        wr |= SQ_A2;
        REQUIRE(popcount(wr) == 3);
    }

    SECTION("=XOR")
    {
    	Board board = Board();
    	U64 wr = board.getWhiteRooks();
        REQUIRE(popcount(wr) == 2);

        wr ^= SQ_A1;
        REQUIRE(popcount(wr) == 1);

        wr = board.getWhiteRooks();
        wr ^= SQ_A2;
        REQUIRE(popcount(wr) == 3);
    }
}
