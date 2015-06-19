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
	constexpr int color_lookup[] = {1, 0};
	void getCastling(std::string const& castleString, int &castlingRights);
	int convertStringToInt(std::string const& fenMoveCounter);
	void getPerformanceIndicator();
	inline constexpr int getOppositeColor(const int color){return color_lookup[color];};
};


#endif /* UTILS_HPP_ */
