
#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <math.h>


namespace TimeManager
{
	constexpr int divider = 50;

	//Note all values are in ms
	int getTimeAllocatedMiliSec(const int wtime, const int btime, const int winc, const int binc, const int colorToPlay)
	{
		if(colorToPlay == WHITE)
		{
			return (wtime+winc - wtime/divider)/divider;
		}
		else
		{
			return (btime+binc - btime/divider)/divider;
		}
	}
};


#endif /* TIMEMANAGER_HPP_ */
