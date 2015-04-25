#include "FastBoard.hpp"

FastBoard::FastBoard() : myWhitePawns(0 | 0xFF << 8 ), myWhiteKnights(0 | (1 << 1) | (1 << 6)), myWhiteBishops(0x0 | (1 << 1) | (1 << 6))
{
	myWhitePieces = myWhitePawns | myWhiteKnights;
	myAllPieces = myBlackPieces | myWhitePieces;
}
