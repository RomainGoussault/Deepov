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
	unsigned int getTimeAllocatedMiliSec(const unsigned int wtime, const unsigned int btime, const unsigned int winc, const unsigned int binc, const unsigned int movestogo, const Color colorToPlay)
	{

		unsigned int allocatedTimeMiliSec;

		if(movestogo == 0)
		{
			if(colorToPlay == WHITE)
			{
				allocatedTimeMiliSec = winc+(wtime - wtime/divider)/divider;
			}
			else
			{
				allocatedTimeMiliSec = binc+(btime - btime/divider)/divider;
			}
		}
		else
		{
			if(colorToPlay == WHITE)
			{
				allocatedTimeMiliSec = winc+(wtime - wtime/(movestogo+3))/(0.7*movestogo+3);
			}
			else
			{
				allocatedTimeMiliSec = binc+(btime - btime/(movestogo+3))/(0.7*movestogo+3);
			}	
		}

		return allocatedTimeMiliSec;
	}
};


#endif /* TIMEMANAGER_HPP_ */
