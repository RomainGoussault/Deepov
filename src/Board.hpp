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
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>

#include "Piece.hpp"
#include "Position.hpp"
#include "Move.hpp"
#include "Color.hpp"

class Board
{
public:

    static const char BOARD_SIZE = 8;


    /*********************************** Constructor ****************************************/

    Board();
    Board(std::string fen); /* I split the FEN to get all his features in the board
    finally we should have class Board = FEN + (TODO) : myNumberMovesWithoutCapture and myPositionRepeat
    I put one move in myMoves if the FEN says enPassant is possible */

    /******************************* Pieces manipulation ************************************/

    void addPiece(PiecePtr piecePtr, Position position);
    void addPiece(PiecePtr piecePtr);
    void removePiece(Position position);

    /******************************** Moves manipulation ************************************/

    bool isFirstMove(); // Use it to know if the position comes from FEN when you want an info on a previous move.
    void executeMove(PiecePtr piecePtr, Position destination);
    void executeMove(Move move); // TODO add promotion moves
    void undoMove(Move move);
    boost::optional<Move> getEnemyLastMove(); // I use boost::optional in case there is no move to return
    std::vector<Move> getLegalMoves(PiecePtr piecePtr); // TODO

    /*********************************** Get attributes **************************************/

    int getTurn() const;
    PiecePtr getPiecePtr(Position position) const;
    std::vector<PiecePtr> getPieces(int color);
    std::vector<PiecePtr> getEnemyPieces(int color);
    PiecePtr getKing(int color); //TODO
    Position getKingPosition(int color); //TODO
    std::vector<Move> getMoves();
    boost::optional<Position> getEnPassantPosition();
    bool getCastling(int castleNumber); /* Same order as FEN :
    0 white king side, 1 white queen side, 2 black king side, 3 black queen side */
    int getHalfMovesCounter();
    int getMovesCounter();


    /******************************* Position manipulation ***********************************/

    bool isPositionFree(Position position);
    bool isPositionOnBoard(Position position);

private:

    std::array<std::array<PiecePtr, BOARD_SIZE>, BOARD_SIZE> myPieces;
    int myColorToPlay;
    std::vector<Move> myMoves;
    boost::optional<Position> myEnPassant;
    bool myCastling[3] ; // Same order as FEN : white king side, white queen side, black king side, black queen side
    int myHalfMovesCounter; // +1 after each color's move
    int myMovesCounter; // +1 move after black's move


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
