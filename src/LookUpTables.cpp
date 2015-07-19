#include "LookUpTables.hpp"

/* List of tables declarations*/
U64 LookUpTables::FRONT_SPANS[2][64];
U64 LookUpTables::FRONT_SQUARES[2][64];

/* Methods */
void LookUpTables::init()
{
    for (int square=0; square<64; ++square)
    {
        FRONT_SQUARES[WHITE][square] = frontBB(square,WHITE);
        FRONT_SQUARES[BLACK][square] = frontBB(square,BLACK);
        FRONT_SPANS[WHITE][square] = FRONT_SQUARES[WHITE][square] | sidesBB(square,WHITE);
        FRONT_SPANS[BLACK][square] = FRONT_SQUARES[BLACK][square] | sidesBB(square,BLACK);
    }
}

U64 LookUpTables::frontBB(const int posIndex,int color)
{
    U64 shift = 0xffffffffffffffff << (posIndex+1); // posIndex+1 for WHITE, take the complement for BLACk
    if (color == BLACK){shift = (~shift) >> 1;}
    return  shift & MASK_FILE[Utils::getFile(posIndex)];
}

U64 LookUpTables::sidesBB(const int posIndex,int color)
{
    int file = Utils::getFile(posIndex);
    U64 leftSide(0);
    U64 rightSide(0);
    if (file > 0){leftSide=frontBB(posIndex-1,color);}
    if (file < 7){rightSide=frontBB(posIndex+1,color);}
    return leftSide | rightSide;
}

