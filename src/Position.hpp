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
	Position deltaX(int delta) const;
	Position deltaY(int delta) const;
	Position deltaXY(int deltaX, int deltaY) const;

	std::string toShortString() const;

private:

	int x;
	int y;
};


inline std::ostream& operator<<(std::ostream &strm, const Position &position)
{
	strm << "[" << position.getX() <<  "," << position.getY() <<  "]";
	return strm;
}

//Overload of the == operator
inline bool operator==(const Position &lhs, const Position &rhs)
{
	return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}


#endif /* POSITION_H_ */
