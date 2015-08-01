#ifndef PIECES_H
#define PIECES_H

namespace Piece
{
    enum PieceType : unsigned int
    {
        PAWN = 0,
        KNIGHT = 1,
        BISHOP = 2,
        ROOK = 3,
        QUEEN = 4,
        KING = 5,
        NO_PIECE_TYPE = 6,
        PIECE_TYPE_NB = 7
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
        W_PIECES = 12,
        B_PIECES = 13,
        NO_PIECE = 14

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
