/*
 * Position.hpp
 *
 *  Created on: 30/08/2014
 *      Author: Romain
 */

#ifndef POSITION_H_
#define POSITION_H_
#include <string>

class Position
{
public:

	Position();
	Position(int _x, int _y);
	int getX();
	int getY();
	Position deltaX(int delta);
	Position deltaY(int delta);
	Position deltaXY(int deltaX, int deltaY);
	std::string print();

private:

	int x;
	int y;
};

#endif /* POSITION_H_ */
