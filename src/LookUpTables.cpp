#include "LookUpTables.hpp"

void LookUpTables::init()
{

}

U64 LookUpTables::frontBB(const int posIndex,int color)
{
    U64 shift = 0xffffffffffffffff << posIndex+1; // posIndex+1 for WHITE, take the complement for BLACk
    if (color == BLACK){shift = ~shift >> 1;}
    return  shift & MASK_FILE[Utils::getFile(posIndex)];
}
