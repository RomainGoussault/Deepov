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
//#include <boost/algorithm/string.hpp>
#include <memory>
#include <array>
#include <random>

#include "Move.hpp"
#include "Types.hpp"
#include "Tables.hpp"
#include "Piece.hpp"
#include "BitBoardUtils.hpp"

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
	inline U64 getWhitePawns() const{return myBitboards[0];}
	inline U64 getWhiteKnights() const{return myBitboards[1];}
	inline U64 getWhiteBishops() const{return myBitboards[2];}
	inline U64 getWhiteRooks() const{return myBitboards[3];}
	inline U64 getWhiteQueens() const{return myBitboards[4];}
	inline U64 getWhiteKing() const{return myBitboards[5];}

	inline U64 getBlackPawns() const{return myBitboards[6];}
	inline U64 getBlackKnights() const{return myBitboards[7];}
	inline U64 getBlackBishops() const{return myBitboards[8];}
	inline U64 getBlackRooks() const{return myBitboards[9];}
	inline U64 getBlackQueens() const{return myBitboards[10];}
	inline U64 getBlackKing() const{return myBitboards[11];}

	inline U64 getPawns(Color color) const{return getBitBoard(Piece::PAWN, color);}
	inline U64 getKnights(Color color) const{return getBitBoard(Piece::KNIGHT, color);}
	inline U64 getBishops(Color color) const{return getBitBoard(Piece::BISHOP, color);}
	inline U64 getRooks(Color color) const{return getBitBoard(Piece::ROOK, color);}
	inline U64 getQueens(Color color) const{return getBitBoard(Piece::QUEEN, color);}
	inline U64 getKing(Color color) const{return getBitBoard(Piece::KING, color);}
	inline Square getKingSquare(Color color) const{return msb(getKing(color));}

	inline U64 getAllPawns() const{return myBitboards[14];}
	inline U64 getAllKnights() const{return myBitboards[15];}
	inline U64 getAllBishops() const{return myBitboards[16];}
	inline U64 getAllRooks() const{return myBitboards[17];}
	inline U64 getAllQueens() const{return myBitboards[18];}
	inline U64 getAllKings() const{return myBitboards[19];}

	inline U64 getWhitePieces() const{return myBitboards[12];}
	inline U64 getBlackPieces() const{return myBitboards[13];}
	inline U64 getAllPieces() const{return myAllPieces;}
	inline U64 getPieces(const Color color) const {return myBitboards[12+color];}
	inline U64 getPinnedPieces() const{return myPinnedPieces;}

	inline U64 getBitBoard(Piece::PieceType pieceType, Color color) const{return myBitboards[pieceType+6*color];};

	inline U64 getAtkFr(Square sq) const {return myAtkFr[sq];};
	inline U64 getAtkTo(Square sq) const {return myAtkTo[sq];};
	inline U64 getKingAttackers() const {return myKingAttackers;};

	U64 getKingAtkTo(Square ksq, Color color) const;

	inline Color getColorToPlay() const {return myColorToPlay;};
	inline std::vector<Move> getMovesHistory() const {return myMoves;};
	inline std::vector<Zkey> getKeysHistory() const {return myKeys;};

	/*  **********  */

	void setBitBoards(const std::string piecesString, const unsigned int rank);
	void updateConvenienceBitboards();
	void updatePinnedPieces();
	void updateAtkFr();

	/* Moves methods */
	bool isMoveLegal(Move &move, bool isCheck); // uses executeMove and undoMove so it can't be const
	void executeMove(Move &move);
	void undoMove(Move &move);
	unsigned int perft(unsigned int depth);
	unsigned int divide(unsigned int depth);
	const Move* getEnemyLastMove() const;

	//Castling Methods
	inline bool isQueenSideCastlingAllowed(const Color color) const {return (myCastling >> (1+2*color)) & 0x1;}
	inline bool isKingSideCastlingAllowed(const Color color) const {return (myCastling >> 2*color) & 0x1;}
	void updateCastlingRights(Move &move);
	void rewindCastlingRights(const Move &move);

    // EP methods
    inline Square getLastEpSquare() const {return myEpSquares.back();}


	//PieceType method
	Piece::Piece findPieceType(const Square position) const;
	Piece::PieceType findPieceType(const Square position, const Color color) const;
	Piece::PieceType findWhitePieceType(const Square position) const;
	Piece::PieceType findBlackPieceType(const Square position) const;

	//Check methods
	bool isCheck(const Color color) const;
	void updateKingAttackers(const Color color);
	inline void updateKingAttackers()
	{
		return updateKingAttackers(myColorToPlay);
	};

	inline bool isCheck() const
	{
		return isCheck(myColorToPlay);
	};

	//Attacked positions
	U64 getAttacksFromSq(const Square position) const;

	inline U64 getKnightAttacks(const Square pos, const Color color) const
	{
		return Tables::ATTACK_TABLE[Piece::KNIGHT][pos] & ~getPieces(color);
	};

	inline U64 getPawnAttacks(const Square square, const Color color) const
	{
		return Tables::PAWN_ATTACK_TABLE[color][square] & ~getPieces(color);
	};

	inline U64 getBishopAttacks(const Square square, const Color color) const
	{
		return MagicMoves::Bmagic(square, getAllPieces()) & ~getPieces(color);
	};

	inline U64 getRookAttacks(const Square square, const Color color) const
	{
		return MagicMoves::Rmagic(square, getAllPieces()) & ~getPieces(color);
	};

	inline U64 getQueenAttacks(const Square square, const Color color) const
	{
		return getBishopAttacks(square,color) | getRookAttacks(square,color);
	};

	inline U64 getKingAttacks(const Square square, const Color color) const
	{
		return Tables::ATTACK_TABLE[Piece::KING][square] & ~getPieces(color);
	};

	inline bool hasBlackCastled() const
	{
		return myHasBlackCastled;
	}

	inline bool hasWhiteCastled() const
	{
		return myHasWhiteCastled;
	}

	/* I keep both functions to compare their performance */
	bool isBitBoardAttacked(U64 bitboard, Color color) const;
	bool isSquareAttacked(Square square, Color color) const; // is square attacked by the opposite color of "Color color"


	/* ************* */
	char getChar(const unsigned int file, const unsigned int rank) const;

	/* This method takes a position as a string (e.g. e4) and returns the index in Little-Endian
    It will replace Utils::getPosition(), this version should be much better.
    In our board model row starts at index 0. a will be 0 and h will be 7 */
	inline unsigned int getIndexFromChar(const std::string position) const {
		return (position[0] - 'a' + 8 * (position[1] - '0' - 1));
	}

	int see(const Square square, Color side);
	int seeCapture(Move captureMove, Color color);
	Piece::PieceType getSmallestAttacker(const Square square, Color side, U64 &attackers);

	//This should be private
	//Zobrist key
	Zkey key;

private:
	std::array<U64, 20> myBitboards;
	U64 myAllPieces;
	U64 myPinnedPieces;

	Color myColorToPlay;
	unsigned int myCastling; /* Same order as FEN
    RIGHT BIT : white king side, white queen side, black king side, black queen side : LEFT BIT
    e.g. the order is 1111 = qkQK */

	bool myHasWhiteCastled;
	bool myHasBlackCastled;

	U64 myAtkTo[SQUARE_NB]; // Locations of pieces that attack to the square
	U64 myAtkFr[SQUARE_NB]; // Attacks from the piece on the square
	U64 myKingAttackers;

	unsigned int myMovesCounter;
	unsigned int myHalfMovesCounter;

	std::vector<Move> myMoves;
	std::vector<Zkey> myKeys;
    std::vector<Square> myEpSquares;


	//TODO : add Zobrist namespace maybe
	Zkey psq[COLOR_NB][Piece::PIECE_TYPE_NB][SQUARE_NB];
	Zkey enPassant[FILE_NB];
	Zkey castling[4];
	Zkey side;

	//move PRNG elsewhere
	std::mt19937_64 rdGen;


	//Move methods
	inline void movePiece(const Square origin, const Square destination, const unsigned int pieceType, const Color color)
	{
		movePiece(origin, destination, myBitboards[pieceType+color*6]);
		key ^= psq[color][pieceType][origin];
		key ^= psq[color][pieceType][destination];
	}

	inline void removePiece(const Square index, const unsigned int pieceType, const Color color)
	{
		removePiece(index, myBitboards[pieceType+color*6]);
		key ^= psq[color][pieceType][index];
	}

	inline void addPiece(const Square index, const unsigned int pieceType, const Color color)
	{
		addPiece(index, myBitboards[pieceType+color*6]);
		key ^= psq[color][pieceType][index];
	}

	inline void removePiece(const Square index, U64 &bitBoard)
	{
		bitBoard &= ~(1LL << index);
	}

	inline void addPiece(const Square index, U64 &bitBoard)
	{
		bitBoard |=  1LL << index;
	}

	inline void movePiece(const Square origin, const Square destination, U64 &bitBoard)
	{
		//Remove piece from origin position
		removePiece(origin, bitBoard);
		//Add piece to destination positions
		addPiece(destination, bitBoard);
	}

	//Zobrist methods
	void initZobristKeys();
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


inline std::ostream& operator<<(std::ostream &strm, const std::vector<Move> &moves) {

	for(unsigned int n = 0; n < moves.size() ; n++)
	{
		strm << moves[n];
	}

	return strm;
}

#endif /* Board_HPP_ */
