/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Tables_HPP_
#define Tables_HPP_

#include "Types.hpp"
#include "Piece.hpp"
#include "Utils.hpp"
#include "MagicMoves.hpp"

namespace Tables
{
	const U64 ALL = 0xffffffffffffffff;
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
    extern U64 FRONT_SPANS[2][SQUARE_NB]; // Squares in front
    extern U64 PAWN_ATTACK_SPANS[2][SQUARE_NB]; // Neighbors files in front
    extern U64 PASSED_PAWN_MASK[2][SQUARE_NB]; // Combination of the 2 previous
    extern U64 ATTACK_TABLE[Piece::PIECE_TYPE_NB][SQUARE_NB]; // ATTACK TABLES for each type;
    extern U64 PAWN_ATTACK_TABLE[Color::COLOR_NB][SQUARE_NB]; // Merge with ATTACK_TABLE ??
    extern U64 LINE_BB[SQUARE_NB][SQUARE_NB];
    extern U64 IN_BETWEEN[SQUARE_NB][SQUARE_NB];
    extern U64 SQUARE_BB[SQUARE_NB];
    extern Square SQUARE[FILE_NB][RANK_NB];

    void init();
    /* The 2 following functions can be changed as const Look Up Tables if we need them faster */
    U64 frontBB(const Square pos,Color color);
    U64 sidesBB(const Square pos,Color color); // his is the BB in front of the pawn at NEIGHBOR_FILES

    // Piece Attacks
    /* See PAWN_ATTACK_SPANS for pawns; 0 for NO_PIECE_TYPE;*/
    /* Non-sliding Pieces*/
    U64 kingAttacks(const Square pos);
    U64 knightAttacks(const Square pos);
    U64 pawnAttacks(const Square pos, Color color);

    /* Sliding Pieces : !!! these tables does not replace moveGen !!! */
    inline U64 bishopAttacks(const Square pos){return MagicMoves::Bmagic(pos, 0x0);};
    inline U64 rookAttacks(const Square pos){return MagicMoves::Rmagic(pos, 0x0);};
    inline U64 queenAttacks(const Square pos)
    {
        return  (bishopAttacks(pos) | rookAttacks(pos));
    };
}


#endif
