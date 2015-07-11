#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"

namespace Pawn
{
	/** Score calculation **/
	int getScore(Board &board);
	int doublePawns(Board &board);
	int passedPawns(Board &board);
	int isolatedPawn(Board &board);


	/** Utils **/
	int countPawns(Board &board, Color color);

};

#endif // Pawn_H
