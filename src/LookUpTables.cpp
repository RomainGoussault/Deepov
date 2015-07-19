#include "LookUpTables.hpp"

/* List of tables declarations*/
U64 LookUpTables::FRONT_SPANS[2][64];

/* Methods */
void LookUpTables::init()
{
    for (int square=0; square<64; ++square)
    {
        LookUpTables::FRONT_SPANS[WHITE][square] = frontBB(square,WHITE) | sidesBB(square,WHITE);
        LookUpTables::FRONT_SPANS[BLACK][square] = frontBB(square,BLACK) | sidesBB(square,BLACK);
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

