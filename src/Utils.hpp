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
#include<math.h>

#include "Board.hpp"

class Utils
{
public:

    /* Bit Hacks*/
    // Source : https://graphics.stanford.edu/~seander/bithacks.html
    static unsigned int countBBBitsSet(U64 x);
    //Some relevant links on this function:
	// https://chessprogramming.wikispaces.com/BitScan
	// http://stackoverflow.com/questions/671815/
	// http://stackoverflow.com/questions/20713017/
	static inline int getMsbIndex(const U64 bitboard) {return (63 - __builtin_clzll(bitboard));}

    static void getCastling(std::string const& castleString, bool (&castleBool)[4]);
    static void getCastling(std::string const& castleString, int &castlingRights);
    static int convertStringToInt(std::string const& fenMoveCounter);
    static int getOppositeColor(const int color){return (1+color)%2;};
    static void getPerformanceIndicator();

private:

};


#endif /* UTILS_HPP_ */
