/*
 * Utils.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"

namespace Utils
{

    /* Bit Hacks*/
    // Source : https://graphics.stanford.edu/~seander/bithacks.html
    unsigned int countBBBitsSet(U64 x);
    //Some relevant links on this function:
	// https://chessprogramming.wikispaces.com/BitScan
	// http://stackoverflow.com/questions/671815/
	// http://stackoverflow.com/questions/20713017/
	inline int getMsbIndex(const U64 bitboard) {return (63 - __builtin_clzll(bitboard));}

    void getCastling(std::string const& castleString, bool (&castleBool)[4]);
    void getCastling(std::string const& castleString, int &castlingRights);
    int convertStringToInt(std::string const& fenMoveCounter);
    inline int getOppositeColor(const int color){return (1+color)%2;};
    void getPerformanceIndicator();
    U64 inBetween(int sq1, int sq2);
};


#endif /* UTILS_HPP_ */
