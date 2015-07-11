#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Color.hpp"
#include "BitBoardUtils.hpp"

namespace Pawn
{
	/** Score calculation **/
	int getScore(Board &board);
	int doublePawns(Board &board);
	int passedPawns(Board &board);
	int isolatedPawn(Board &board);


	/** Utils **/
	int countPawns(Board &board, int color);

};

#endif // Pawn_H
