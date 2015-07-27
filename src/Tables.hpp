#ifndef Tables_HPP_
#define Tables_HPP_

#include "Color.hpp"
#include "Utils.hpp"

namespace Tables
{
    const U64 MASK_RANK[]={0xFF,
                                0xFF00,
                                0xFF0000,
                                0xFF000000,
                                0xFF00000000,
                                0xFF0000000000,
                                0xFF000000000000,
                                0xFF00000000000000
                                };

    const U64 MASK_FILE[]={0x0101010101010101,
                                0x202020202020202,
                                0x404040404040404,
                                0x808080808080808,
                                0x1010101010101010,
                                0x2020202020202020,
                                0x4040404040404040,
                                0x8080808080808080
                                };

    const U64 CLEAR_RANK[]={0xFFFFFFFFFFFFFF00,
                                0xFFFFFFFFFFFF00FF,
                                0xFFFFFFFFFF00FFFF,
                                0xFFFFFFFF00FFFFFF,
                                0xFFFFFF00FFFFFFFF,
                                0xFFFF00FFFFFFFFFF,
                                0xFF00FFFFFFFFFFFF,
                                0x00FFFFFFFFFFFFFF
                                };

    const U64 CLEAR_FILE[]={0xFEFEFEFEFEFEFEFE,
                                0xFDFDFDFDFDFDFDFD,
                                0xFBFBFBFBFBFBFBFB,
                                0xF7F7F7F7F7F7F7F7,
                                0xEFEFEFEFEFEFEFEF,
                                0xDFDFDFDFDFDFDFDF,
                                0xBFBFBFBFBFBFBFBF,
                                0x7F7F7F7F7F7F7F7F
                                };

    const U64 ROOK_INITIAL_POS = {0x8100000000000081};

    const U64 NEIGHBOR_FILES[]={0x202020202020202,
                                0x505050505050505,
                                0xa0a0a0a0a0a0a0a,
                                0x1414141414141414,
                                0x2828282828282828,
                                0x5050505050505050,
                                0xa0a0a0a0a0a0a0a0,
                                0x4040404040404040};

    /* Extern tables (i.e. declared but not defined) */
    /* In 2 for colors, 64 for squares */
    extern U64 FRONT_SPANS[2][64]; // Squares in front
    extern U64 PAWN_ATTACK_SPANS[2][64]; // Neighbors files in front
    extern U64 PASSED_PAWN_MASK[2][64]; // Combination of the 2 previous
    extern U64 ATTACK_TABLE[Piece::PIECE_TYPE_NB][64]; // ATTACK TABLES for each type


    void init();
    /* The 2 following functions can be changed as const Look Up Tables if we need them faster */
    U64 frontBB(const unsigned int pos,Color color);
    U64 sidesBB(const unsigned int pos,Color color); // his is the BB in front of the pawn at NEIGHBOR_FILES

    // Piece Attacks
    U64 getKingAttacks(const unsigned int pos) const;
    U64 getQueenAttacks(const unsigned int pos) const;
    U64 getRookAttacks(const unsigned int pos) const;
    U64 getBishopAttacks(const unsigned int pos) const;
    U64 getKnightAttacks(const unsigned int pos) const;
}


#endif
