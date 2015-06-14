/*
 * Board.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef Board_HPP_
#define Board_HPP_

#include <cstdint>
#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>


typedef std::uint64_t U64;

#include "Move.hpp"
#include "LookUpTables.hpp"
#include "Color.hpp"


/*
Note: We use Little-Endian Rank-File Mapping
The bitboard (U64) in binary representation is  H8-G8-F8-....-C1-B1-A1
Left shift '<<' means +1 on the chessboard
Right shift '>>' means -1 on the chessboard
The compass is:
    +7  +8  +9
    -1   0  +1
    -9  -8  -7
*/


class Board : public std::enable_shared_from_this<Board>
{
public:

	Board();
	Board(const std::string fen);

	/* BitBoard getters */
	inline U64 getWhitePawns() const{return myWhitePawns;}
	inline U64 getWhiteKnights() const{return myWhiteKnights ;}
	inline U64 getWhiteBishops() const{return myWhiteBishops;}
	inline U64 getWhiteRooks() const{return myWhiteRooks;}
	inline U64 getWhiteQueens() const{return myWhiteQueens;}
	inline U64 getWhiteKing() const{return myWhiteKing;}

	inline U64 getBlackPawns() const{return myBlackPawns;}
	inline U64 getBlackKnights() const{return myBlackKnights;}
	inline U64 getBlackBishops() const{return myBlackBishops;}
	inline U64 getBlackRooks() const{return myBlackRooks;}
	inline U64 getBlackQueens() const{return myBlackQueens;}
	inline U64 getBlackKing() const{return myBlackKing;}

	inline U64 getWhitePieces() const{return myWhitePieces;}
	inline U64 getBlackPieces() const{return myBlackPieces;}
	inline U64 getAllPieces() const{return myAllPieces;}
	inline U64 getPieces(const int color) const {return color == WHITE ? getWhitePieces() : getBlackPieces();}
	inline U64 getPinnedPieces() const{return myPinnedPieces;}

    void updatePinnedPieces();


	inline bool getColorToPlay() const {return myColorToPlay;};
	inline std::vector<Move> getMovesHistory() const {return myMoves;};

	/*  **********  */

	void setBitBoards(const std::string piecesString, const int rank);
	void updateConvenienceBitboards();

	/* Moves methods */
    bool isMoveLegal(Move &move, bool isCheck); // uses executeMove and undoMove so it can't be const
    void executeMove(Move &move);
    void undoMove(Move &move);
    int perft(int depth);
    int divide(int depth);
    boost::optional<Move> getEnemyLastMove() const; // I use boost::optional in case there is no move to return

    //Castling Methods
    bool isQueenSideCastlingAllowed(const int color) const {return ((myCastling >> (1+2*color)) & 0x1);}
    bool isKingSideCastlingAllowed(const int color) const {return ((myCastling >> 2*color) & 0x1);}
    void updateCastlingRights(Move &move);
    void rewindCastlingRights(const Move &move);


    //PieceType method
    int findPieceType(const int position, const int color) const;
    int findWhitePieceType(const int position) const;
    int findBlackPieceType(const int position) const;

    //Check methods
    bool isCheck(const int color) const;

    //Attacked positions
    U64 getAttackedPositions(const int color) const;
    U64 getKingAttackedPositions(const int& color) const;
    U64 getKingDestinations(const U64 kingPos, const int& color) const;
    U64 getQueenAttackedPositions(const int& color) const;
    U64 getRookAttackedPositions(const int& color) const;
    U64 getBishopAttackedPositions(const int& color) const;
    U64 getKnightDestinations(const int knightIndex, const int& color) const;
    U64 getKnightAttackedPositions(const int& color) const;
    U64 getPawnAttackedPositions(const int& color) const;
    U64 getWhitePawnAttackedPositions() const;
    U64 getBlackPawnAttackedPositions() const;

	/* ************* */
    char getChar(const int file, const int rank) const;

    /* This method takes a position as a string (e.g. e4) and returns the index in Little-Endian
    It will replace Utils::getPosition(), this version should be much better.
    In our board model row starts at index 0. a will be 0 and h will be 7 */
    inline int getIndexFromChar(const std::string position) const {return(position[0] - 'a'+8*(position[1] - '0'-1));};


private:

	U64 myWhitePawns;
	U64 myWhiteKnights;
	U64 myWhiteBishops;
	U64 myWhiteRooks;
	U64 myWhiteQueens;
	U64 myWhiteKing;

	U64 myBlackPawns;
	U64 myBlackKnights;
	U64 myBlackBishops;
	U64 myBlackRooks;
	U64 myBlackQueens;
	U64 myBlackKing;

	U64 myWhitePieces;
	U64 myBlackPieces;
	U64 myAllPieces;
	U64 myPinnedPieces;

	bool myColorToPlay;
    int myMovesCounter;
    int myHalfMovesCounter;
    int myCastling; /* Same order as FEN
    RIGHT BIT : white king side, white queen side, black king side, black queen side : LEFT BIT
    e.g. the order is 1111 = qkQK */

    std::vector<Move> myMoves;

    void movePiece(const int origin, const int destination, const int pieceType, const int color);
    void movePiece(const int origin, const int destination, U64 &bitboard);
    void removePiece(const int index, const int pieceType, const int color);
    void addPiece(const int index, const int pieceType, const int color);

    inline void removePiece(const int index, U64 &bitBoard){bitBoard &= ~(1LL << index);}
    inline void addPiece(const int index, U64 &bitBoard){bitBoard |=  1LL << index;}
};


inline std::ostream& operator<<(std::ostream &strm, const Board &Board) {

	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(int file = 0; file < 8 ; file++)
		{
			strm << Board.getChar(file, rank) << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm;
}

#endif /* Board_HPP_ */
