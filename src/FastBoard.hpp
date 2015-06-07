/*
 * FastBoard.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */
#ifndef FASTBOARD_HPP_
#define FASTBOARD_HPP_

#include <cstdint>
#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <memory>


//#include "Utils.hpp"
//#define Rank_Size 8
//#define Board_Size 64  // to be renamed after Board.hpp is removed
typedef std::uint64_t U64;

#include "FastMove.hpp"
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


class FastBoard : public std::enable_shared_from_this<FastBoard>
{
public:

	FastBoard();
	FastBoard(const std::string fen);

	/* Get the bitboards */
    U64 getWhitePawns() const;
	U64 getWhiteKnights() const;
	U64 getWhiteBishops() const;
	U64 getWhiteRooks() const;
	U64 getWhiteQueens() const;
	U64 getWhiteKing() const;

	U64 getBlackPawns() const;
	U64 getBlackKnights() const;
	U64 getBlackBishops() const;
	U64 getBlackRooks() const;
	U64 getBlackQueens() const;
	U64 getBlackKing() const;

	U64 getWhitePieces() const;
	U64 getBlackPieces() const;
	U64 getAllPieces() const;
	U64 getPieces(const int color) const {return color == WHITE ? getWhitePieces() : getBlackPieces();}

	inline bool getColorToPlay() const {return myColorToPlay;};
	inline std::vector<FastMove> getMovesHistory() const {return myMoves;};

	/*  **********  */

	void setBitBoards(const std::string piecesString, const int rank);
	void updateConvenienceBitboards();

	//Some relevant links on this function:
	// https://chessprogramming.wikispaces.com/BitScan
	// http://stackoverflow.com/questions/671815/
	// http://stackoverflow.com/questions/20713017/
	static inline int getMsbIndex(const U64 bitboard) {return (63 - __builtin_clzll(bitboard));}
	/* TODO : put this is Utils ?? */


	/* Moves methods */
    bool isMoveLegal(FastMove &move); // uses executeMove and undoMove so it can't be const
    void executeMove(FastMove &move);
    void undoMove(FastMove &move);
    int perft(int depth);
    int divide(int depth);
    boost::optional<FastMove> getEnemyLastMove() const; // I use boost::optional in case there is no move to return

    //Castling Methods
    bool isQueenSideCastlingAllowed(const int color) const {return (myCastling >> (1+2*color)) & 0b1;}
    bool isKingSideCastlingAllowed(const int color) const {return (myCastling >> 2*color) & 0b1;}
    void updateCastlingRights(FastMove &move);
    void rewindCastlingRights(FastMove &move);


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

    //Static functions
    static bool isBitSet(U64 bitBoard, const int x, const int y);
    static std::string printBitBoard(const U64 &bitBoard);

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

	bool myColorToPlay;
    int myMovesCounter;
    int myHalfMovesCounter;
    int myCastling; /* Same order as FEN
    RIGHT BIT : white king side, white queen side, black king side, black queen side : LEFT BIT
    e.g. the order is 1111 = qkQK */

    std::vector<FastMove> myMoves;

    void movePiece(const int origin, const int destination, const int pieceType, const int color);
    void movePiece(const int origin, const int destination, U64 &bitboard);
    void removePiece(const int index, const int pieceType, const int color);
    void addPiece(const int index, const int pieceType, const int color);

    inline void removePiece(const int index, U64 &bitBoard){bitBoard &= ~(1LL << index);}
    inline void addPiece(const int index, U64 &bitBoard){bitBoard |=  1LL << index;}
};


inline std::ostream& operator<<(std::ostream &strm, const FastBoard &fastBoard) {

	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(int file = 0; file < 8 ; file++)
		{
			strm << fastBoard.getChar(file, rank) << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	return strm;
}

#endif /* FASTBOARD_HPP_ */
