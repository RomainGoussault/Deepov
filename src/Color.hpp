/*
 * Color.hpp
 *
 *  Created on: 31 août 2014
 *      Author: Romain
 */

#ifndef COLOR_HPP_
#define COLOR_HPP_

class Color {

    Color *opposite_p;

public:
    Color(Color *opposite_pArg) : opposite_p(opposite_pArg) {}

    Color &opposite() { return *opposite_p; }

    static Color WHITE, BLACK;
};
#endif /* COLOR_HPP_ */
