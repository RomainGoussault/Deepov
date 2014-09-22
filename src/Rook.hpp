/*
 * Rook.hpp
 *
 *  Created on: 1 sept. 2014
 *      Author: Romain
 */

#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "Position.hpp"


class Rook
{
public:

	Rook(Position position, int color);

private:

	Position& myPosition;
	int myColor;
};



#endif /* ROOK_HPP_ */
