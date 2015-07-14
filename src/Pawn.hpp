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
	int initScore(const Board &board);
    int countPawnsInFile(const Board &board, const int file, const int color);
	int initDoubledPawns(const Board &board);
	int passedPawns(const Board &board);
	int isolatedPawn(const Board &board);

	/** Utils **/
	int countPawns(const Board &board, const int color);

};

#endif // Pawn_H
