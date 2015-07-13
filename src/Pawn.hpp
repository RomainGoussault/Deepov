#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Color.hpp"
#include "BitBoardUtils.hpp"

namespace Pawn
{
	const static unsigned int DOUBLED_PAWN_PENALTY = 10;
	const static unsigned int ISOLATED_PAWN_PENALTY = 10;
	const static unsigned int PASSED_PAWN_BONUS = 10;

	/** Score calculation **/
	int getScore(Board &board);
	int doubledPawns(Board &board);
	int passedPawns(Board &board);
	int isolatedPawn(Board &board);


	/** Utils **/
	int countPawns(Board &board, int color);

};

#endif // Pawn_H
