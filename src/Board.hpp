/*
 * Board.hpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <array>
#include <vector>

#include "Piece.hpp"
#include "Position.hpp"
#include "Move.hpp"


class Board
{
public:

    static const char BOARD_SIZE = 7;
    Board();

    void addPiece(Piece piece, Position position);
    void addPiece(Piece piece);

    Piece getPiece(Position position);
    std::vector<Piece> getPieces(int color); //TODO
    std::vector<Piece> getEnnemyPieces(Position position);//TODO
    Piece getKing(int color); //TODO
    Position getKingPosition(int color); //TODO

    bool isPositionFree(Position position);
    bool isPositionOnBoard(Position position);

    std::vector<Move> getLegalMoves(Piece piece); // TODO

private:

    std::array<std::array<Piece, BOARD_SIZE>, BOARD_SIZE> myPieces;
};


#endif /* BOARD_HPP_ */
