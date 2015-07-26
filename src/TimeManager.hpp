
#ifndef TIMEMANAGER_HPP_
#define TIMEMANAGER_HPP_

#include <vector>
#include <iostream>
#include <math.h>


namespace TimeManager
{
	constexpr unsigned int divider = 50;

	//Note all values are in ms
	unsigned int getTimeAllocatedMiliSec(const unsigned int wtime, const unsigned int btime, const unsigned int /*winc*/, const unsigned int /*binc*/, const unsigned int colorToPlay)
	{
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
