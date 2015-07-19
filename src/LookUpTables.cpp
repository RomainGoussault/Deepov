#include "LookUpTables.hpp"

void LookUpTables::init()
{

}

U64 LookUpTables::frontBB(const int posIndex,int color)
{
    int shift = posIndex+(63-2*posIndex)*color; // posIndex for WHITE, 63-posIndex for BLACK
    return  (0xffffffffffffffff << shift) & MASK_FILE[Utils::getFile(posIndex)];
}
