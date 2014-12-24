/*
 * Position.cpp
 *
 *  Created on: 30/08/2014
 *      Author: Romain
 */
#include "Position.hpp"
#include <array>
#include <sstream>
#include <string>

Position::Position() : x(0), y(0)
{
}

Position::Position(int _x, int _y) : x(_x), y(_y)
{
}

Position Position::deltaX(int delta) const
{
	return Position(x + delta, y);
}

Position Position::deltaY(int delta) const
{
	return Position(x, y + delta);
}

Position Position::deltaXY(int deltaX, int deltaY) const
{
	return Position(x + deltaX, y + deltaY);
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

std::string Position::toShortString() const
{
	std::array<std::string,8> letters = {"a", "b", "c", "d", "e", "f", "g", "h"};
	int yy = y + 1;

	std::stringstream ss;
	ss << letters[x] << yy;

	return ss.str();;
}
