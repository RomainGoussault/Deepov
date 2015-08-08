#include "catch.hpp"
#include "Tables.hpp"
#include "Types.hpp"

TEST_CASE( "Tables" )
{
    Tables::init();

    SECTION("Bitboard calculations")
    {
        Square posIndex = static_cast<Square>(10);
        U64 frontMask=Tables::frontBB(posIndex,WHITE);
        REQUIRE(frontMask == 0x404040404040000LL);

        frontMask=Tables::frontBB(posIndex,BLACK);
        REQUIRE(frontMask == 0x4LL);
    }

    SECTION("Pawn tables")
    {
        REQUIRE(Tables::PASSED_PAWN_MASK[WHITE][34] == 0xe0e0e0000000000LL);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][34] == 0xe0e0e0eLL);
        REQUIRE(Tables::FRONT_SPANS[WHITE][34] == 0x404040000000000LL);
        REQUIRE(Tables::FRONT_SPANS[BLACK][34] == 0x4040404LL);
        REQUIRE(Tables::PASSED_PAWN_MASK[BLACK][44] == 0x3838383838LL);
    }

    SECTION("Attack Tables")
    {
        REQUIRE(Tables::ATTACK_TABLE[Piece::KNIGHT][34] == 0xa1100110a0000LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::BISHOP][34] == 0x20110a000a112040LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::KING][34] == 0xe0a0e000000LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::PAWN][34] == 0x0LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::ROOK][34] == 0x40404fb04040404LL);

        REQUIRE(Tables::ATTACK_TABLE[Piece::KNIGHT][12] == 0x28440044LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::BISHOP][12] == 0x18244280028LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::KING][12] == 0x382838LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::PAWN][12] == 0x0LL);
        REQUIRE(Tables::ATTACK_TABLE[Piece::ROOK][12] == 0x101010101010ef10LL);
    }
}
