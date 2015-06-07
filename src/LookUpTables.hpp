#ifndef LOOKUPTABLES_HPP_
#define LOOKUPTABLES_HPP_

#include <cstdint>
#include <iostream>
#include <bitset>
#include "FastBoard.hpp"


class LookUpTables
{
public:
    static const U64 CLEAR_RANK[8];
    static const U64 MASK_RANK[8];
    static const U64 CLEAR_FILE[8];
    static const U64 MASK_FILE[8];

    static const U64 ROOK_INITIAL_POS;

private:

};


#endif
