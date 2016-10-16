/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
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
