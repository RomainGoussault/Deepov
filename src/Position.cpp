/*
 * Position.cpp
 *
 *  Created on: 30/08/2014
 *      Author: Romain
 */
#include "Position.hpp"
#include <string>

Position::Position() : x(0), y(0)
{
}

Position::Position(int _x, int _y) : x(_x), y(_y)
{
}

Position Position::deltaX(int delta)
{
	return Position(x + delta, y);
}

Position Position::deltaY(int delta)
{
	return Position(x, y + delta);
}

Position Position::deltaXY(int deltaX, int deltaY)
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
