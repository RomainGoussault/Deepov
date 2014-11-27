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


class Utils
{
public:
    static std::vector<PiecePtr> getPiecesFromFen(std::string fen);
    static std::vector<PiecePtr> getPieces(std::string piecesString, int rank);
    static void getCastling(std::string &castleString, bool (&castleBool)[3]);
    static Position getSquare(std::string &fenSquare);
    static Position getEnPassantPosition(std::string fen); // TODO

private:

};


#endif /* UTILS_HPP_ */
