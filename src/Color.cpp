/*
 * Color.cpp
 *
 *  Created on: 31 août 2014
 *      Author: Romain
 */

#include "Color.hpp"

Color Color::getOppositeColor(Color c) {
    static Color opposite[] = {WHITE, BLACK};
    return opposite[c];
}

