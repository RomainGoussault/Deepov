/*
 * Utils.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>
#include <iostream>


#include<math.h>

class Utils
{
public:
    static void getCastling(std::string const& castleString, bool (&castleBool)[4]);
    static void getCastling(std::string const& castleString, int &castlingRights);
    static int convertStringToInt(std::string const& fenMoveCounter);
    static int getOppositeColor(const int color){return (1+color)%2;};
    static void getPerformanceIndicator();

private:

};


#endif /* UTILS_HPP_ */
