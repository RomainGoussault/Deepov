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

#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <math.h>


namespace TimeManager
{
	unsigned int divider = 50; //this value is set by the timeDivider Option

	//Note all values are in ms
	unsigned int getTimeAllocatedMiliSec(const unsigned int wtime, const unsigned int btime, const unsigned int winc, const unsigned int binc, const Color colorToPlay)
	{
		if(colorToPlay == WHITE)
		{
			return winc/4+(wtime - wtime/divider)/divider;
		}
		else
		{
			return binc/4+(btime - btime/divider)/divider;
		}
	}
};


#endif /* TIMEMANAGER_HPP_ */
