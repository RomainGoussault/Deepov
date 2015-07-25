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
	void getCastling(std::string const& castleString, unsigned int &castlingRights);
	unsigned int convertStringToInt(std::string const& fenMoveCounter);
	void getPerformanceIndicator();
	inline constexpr unsigned int getOppositeColor(const unsigned int color){return color ^ 1;};
	inline unsigned int getFile(const unsigned int positionIndex){return positionIndex%8;};
};


#endif /* UTILS_HPP_ */
