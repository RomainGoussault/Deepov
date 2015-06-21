
#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <math.h>


namespace TimeManager
{
	constexpr int divider = 50;

	//Note all values are in ms
	int getTimeAllocatedMiliSec(int wtime, int btime, int winc, int binc, int colorToPlay)
	{
		//Todo write something
		if(colorToPlay == WHITE)
		{
			return (wtime - wtime/divider)/divider;
		}
		else
		{
			return (btime - btime/divider)/divider;
		}
	}
};


#endif /* TIMEMANAGER_HPP_ */
