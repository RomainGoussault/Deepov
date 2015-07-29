#include "catch.hpp"
#include "Tables.hpp"
#include "Color.hpp"

TEST_CASE( "Tables" )
{
    Tables::init();

    SECTION("Bitboard calculations")
    {
        unsigned int posIndex = 10;
        U64 frontMask=Tables::frontBB(posIndex,WHITE);
        REQUIRE(frontMask == 0x404040404040000);

        frontMask=Tables::frontBB(posIndex,BLACK);
        REQUIRE(frontMask == 0x4);
    }

    SECTION("Pawn tables")
    {
        REQUIRE(Tables::PASSED_PAWN_MASK[WHITE][34] == 0xe0e0e0000000000);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][34] == 0xe0e0e0e);
        REQUIRE(Tables::FRONT_SPANS[WHITE][34] == 0x404040000000000);
        REQUIRE(Tables::FRONT_SPANS[BLACK][34] == 0x4040404);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][44] == 0x3838383838);
    }

    SECTION("Attack Tables")
    {
        REQUIRE(Tables::ATTACK_TABLE[Piece::KNIGHT][34] == 0xa1100110a0000);
        REQUIRE(Tables::ATTACK_TABLE[Piece::BISHOP][34] == 0x20110a000a112040);
        REQUIRE(Tables::ATTACK_TABLE[Piece::KING][34] == 0xe0a0e000000);
        REQUIRE(Tables::ATTACK_TABLE[Piece::PAWN][34] == 0x0);
        REQUIRE(Tables::ATTACK_TABLE[Piece::ROOK][34] == 0x40404fb04040404);

        REQUIRE(Tables::ATTACK_TABLE[Piece::KNIGHT][12] == 0x28440044);
        REQUIRE(Tables::ATTACK_TABLE[Piece::BISHOP][12] == 0x18244280028);
        REQUIRE(Tables::ATTACK_TABLE[Piece::KING][12] == 0x382838);
        REQUIRE(Tables::ATTACK_TABLE[Piece::PAWN][12] == 0x0);
        REQUIRE(Tables::ATTACK_TABLE[Piece::ROOK][12] == 0x101010101010ef10);
    }
}
