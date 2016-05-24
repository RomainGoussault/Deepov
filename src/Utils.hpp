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

#include "Types.hpp"

class Board;

namespace Utils
{
	void getCastling(std::string const& castleString, unsigned int &castlingRights);
	unsigned int convertStringToInt(std::string const& fenMoveCounter);
	void getPerformanceIndicator();
	inline constexpr Color getOppositeColor(const Color color){return Color(color ^ 1);};
	inline unsigned int getFile(const Square positionIndex){return positionIndex%8;};
    std::string Move16ToShortString(const Move16 shortMove);
};


#endif /* UTILS_HPP_ */
