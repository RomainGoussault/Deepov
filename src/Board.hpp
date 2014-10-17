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
#include <memory>

#include "Piece.hpp"
#include "Position.hpp"
#include "Move.hpp"
#include "Color.hpp"

class Board
{
public:

    static const char BOARD_SIZE = 8;

    Board();
    Board(std::string fen);

    void addPiece(PiecePtr piecePtr, Position position);
    void addPiece(PiecePtr piecePtr);
    void removePiece(Position position);

    int getTurn() const;
    void executeMove(PiecePtr piecePtr, Position destination);
    void executeMove(Move move);
    void undoMove(Move move);


    PiecePtr getPiecePtr(Position position) const;
    std::vector<PiecePtr> getPieces(int color); //TODO
    std::vector<PiecePtr> getEnnemyPieces(int color);//TODO
    PiecePtr getKing(int color); //TODO
    Position getKingPosition(int color); //TODO

    bool isPositionFree(Position position);
    bool isPositionOnBoard(Position position);

    std::vector<Move> getLegalMoves(PiecePtr piecePtr); // TODO


private:

    std::array<std::array<PiecePtr, BOARD_SIZE>, BOARD_SIZE> myPieces;
    int myColorToPlay;
    std::vector<Move> myMoves;

};

inline std::ostream& operator<<(std::ostream &strm, const Board &board)
{
		std::string boardStr;

		for(int i = 7; i >= 0 ; i--)
		{
			strm << i << "|  ";

			for(int j = 0; j < 8 ; j++)
			{
				Position position(j,i);
				PiecePtr piecePtr = board.getPiecePtr(position);
				
				if(piecePtr)
				{
					char piecechar = piecePtr->getChar();
					piecechar = piecePtr->getColor() == WHITE ? toupper(piecechar) : piecechar;
		            boardStr = piecechar;
				}
				else
				{
		            boardStr = "*";
				}

				strm << boardStr <<  " ";
			}

			strm << std::endl;
		}

		strm << "   ________________" << std::endl;
		strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm;
}
#endif /* BOARD_HPP_ */
