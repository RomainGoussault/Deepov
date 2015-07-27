#ifndef PIECES_H
#define PIECES_H

namespace Piece
{
    enum PieceType : unsigned int
    {
        PAWN_TYPE = 0,
        KNIGHT_TYPE = 1,
        BISHOP_TYPE = 2,
        ROOK_TYPE = 3,
        QUEEN_TYPE = 4,
        KING_TYPE = 5,
        NO_PIECE_TYPE= 6
    };

    enum PieceValue : unsigned int
    {
        QUEEN_VALUE = 900,
        ROOK_VALUE = 500,
        KING_VALUE = 10000,
        KNIGHT_VALUE = 310,
        BISHOP_VALUE = 325,
        PAWN_VALUE = 100
    };
};

#endif // PIECES_H
