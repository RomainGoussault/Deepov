/*
 * Utils.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector>

#include "Piece.hpp"
#include<math.h>


class Utils
{
public:
    static std::vector<PiecePtr> getPiecesFromFen(std::string fen);
    static std::vector<PiecePtr> getPieces(std::string piecesString, int rank);
    static void getCastling(std::string const& castleString, bool (&castleBool)[3]);
    static Position getPosition(std::string const& fenSquare);
    static int convertStringToInt(std::string const& fenMoveCounter);
    static int getOppositeColor(const int color){return (1+color)%2;};
private:

};


#endif /* UTILS_HPP_ */
