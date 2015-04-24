#include "FastBoard.hpp"

FastBoard::FastBoard() :
		myWhitePawns(0x000000000000FF00), myWhiteKnights(0x0 | (1 << 1) | (1 << 6))
{
	myWhitePieces = myWhitePawns | myWhiteKnights;
}
