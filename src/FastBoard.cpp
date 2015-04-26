#include "FastBoard.hpp"




FastBoard::FastBoard() : myWhitePawns(0 | 0xFF << 8 ), myWhiteKnights(0 | (1 << 1) | (1 << 6)), myWhiteBishops(0x0 | (1 << 1) | (1 << 6))
{
	myWhitePieces = myWhitePawns | myWhiteKnights;
	myAllPieces = myBlackPieces | myWhitePieces;
}

	/* Get the bitboards */

U64 FastBoard::getWhitePawns() const{return myWhitePawns;}

U64 FastBoard::getWhiteKnights() const{return myWhiteKnights ;}
U64 FastBoard::getWhiteBishops() const{return myWhiteBishops;}
U64 FastBoard::getWhiteRooks() const{return myWhiteRooks;}
U64 FastBoard::getWhiteQueens() const{return myWhiteQueens;}
U64 FastBoard::getWhiteKing() const{return myWhiteKing;}

U64 FastBoard::getBlackPawns() const{return myBlackPawns;}
U64 FastBoard::getBlackKnights() const{return myBlackKnights;}
U64 FastBoard::getBlackBishops() const{return myBlackBishops;}
U64 FastBoard::getBlackRooks() const{return myBlackRooks;}
U64 FastBoard::getBlackQueens() const{return myBlackQueens;}
U64 FastBoard::getBlackKing() const{return myBlackKing;}

U64 FastBoard::getWhitePieces() const{return myWhitePieces;}
U64 FastBoard::getBlackPieces() const{return myBlackPieces;}
U64 FastBoard::getAllPieces() const{return myAllPieces;}

	/*  **********  */

    /* Moves methods */
std::vector<FastMove> getMoves() const
{
    return myMoves;
}
	/* ************* */

