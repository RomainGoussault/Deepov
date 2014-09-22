/*
 * Color.hpp
 *
 *  Created on: 31 août 2014
 *      Author: Romain
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

class Color {
public:
	enum Color {BLACK, WHITE};
	Color getOppositeColor(Color c);
};
#endif /* COLOR_HPP_ */
