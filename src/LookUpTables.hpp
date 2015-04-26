#ifndef LOOKUPTABLES_HPP_
#define LOOKUPTABLES_HPP_

#include <cstdint>
#include <iostream>
#include <bitset>
#include "FastBoard.hpp"


class LookUpTables
{
public:
    static U64 ClearRank[8];
    const static U64 MaskRank0 = 0x00000000000000FF;
    static U64 ClearFile[8];
    static U64 MaskFile[8];

    /* MaskRank[1]=
    MaskRank[2]=MaskRank[1] << _RankSize_;
    MaskRank[3]=MaskRank[2] << _RankSize_;
    MaskRank[4]=MaskRank[3] << _RankSize_;
    MaskRank[5]=MaskRank[4] << _RankSize_;
    MaskRank[6]=MaskRank[5] << _RankSize_;
    MaskRank[7]=MaskRank[6] << _RankSize_;
    MaskRank[8]=MaskRank[7] << _RankSize_;


    MaskFile[1]=0x0101010101010101;
    MaskFile[2]=MaskFile[1] << 1;
    MaskFile[3]=MaskFile[2] << 1;
    MaskFile[4]=MaskFile[3] << 1;
    MaskFile[5]=MaskFile[4] << 1;
    MaskFile[6]=MaskFile[5] << 1;
    MaskFile[7]=MaskFile[6] << 1;
    MaskFile[8]=MaskFile[7] << 1;


    ClearRank[1]=0xFFFFFFFFBFFFFF00;
    ClearRank[2]=ClearRank[1] << _RankSize_ + MaskRank[1];
    ClearRank[3]=ClearRank[2] << _RankSize_ + MaskRank[2];
    ClearRank[4]=ClearRank[3] << _RankSize_ + MaskRank[3];
    ClearRank[5]=ClearRank[4] << _RankSize_ + MaskRank[4];
    ClearRank[6]=ClearRank[5] << _RankSize_ + MaskRank[5];
    ClearRank[7]=ClearRank[6] << _RankSize_ + MaskRank[6];
    ClearRank[8]=ClearRank[7] << _RankSize_ + MaskRank[7];

    ClearRank[1]=0xFFFFFFFFBFFFFF00;
    ClearRank[2]=ClearRank[1] << _RankSize_ + MaskRank[1];
    ClearRank[3]=ClearRank[2] << _RankSize_ + MaskRank[2];
    ClearRank[4]=ClearRank[3] << _RankSize_ + MaskRank[3];
    ClearRank[5]=ClearRank[4] << _RankSize_ + MaskRank[4];
    ClearRank[6]=ClearRank[5] << _RankSize_ + MaskRank[5];
    ClearRank[7]=ClearRank[6] << _RankSize_ + MaskRank[6];
    ClearRank[8]=ClearRank[7] << _RankSize_ + MaskRank[7];*/
private:

};


#endif
