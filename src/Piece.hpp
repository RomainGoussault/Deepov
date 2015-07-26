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
        NO_PIECE_TYPE=6
    };

    enum Piece: unsigned int
    {
        W_PAWN = 0,
        W_KNIGHT = 1,
        W_BISHOP = 2,
        W_ROOK = 3,
        W_QUEEN = 4,
        W_KING = 5,
        B_PAWN = 6,
        B_KNIGHT = 7,
        B_BISHOP = 8,
        B_ROOK = 9,
        B_QUEEN = 10,
        B_KING = 11,
        NO_PIECE = 12

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
