/*
 * Position.hpp
 *
 *  Created on: 30/08/2014
 *      Author: Romain
 */

#ifndef POSITION_H_
#define POSITION_H_
#include <string>
#include <iostream>

class Position
{
public:

	Position();
	Position(int _x, int _y);
	int getX() const;
	int getY() const;
	Position deltaX(int delta);
	Position deltaY(int delta);
	Position deltaXY(int deltaX, int deltaY);
	std::string print();

private:

	int x;
	int y;
};


inline std::ostream& operator<<(std::ostream &strm, const Position &position)
{
	strm << "[" << position.getX() <<  "," << position.getY() <<  "]" <<std::endl;
	return strm;
}

#endif /* POSITION_H_ */
