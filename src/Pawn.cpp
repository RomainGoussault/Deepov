/*
 */

#include "Pawn.hpp"

int Pawn::getScore(Board &board)
{
	return doublePawns(board)+passedPawns(board)+isolatedPawn(board);
}

int Pawn::doublePawns(Board &board)
{
	return 0;
}

int Pawn::passedPawns(Board &board)
{
	return 0;
}

int Pawn::isolatedPawn(Board &board)
{
	return 0;
}

int Pawn::countPawns(Board &board, int color)
{
	int count;
	if (color == WHITE)
	{
		count=BitBoardUtils::countBBBitsSet(board.getWhitePawns());
	}
	else 
	{
		count=BitBoardUtils::countBBBitsSet(board.getBlackPawns());
	}
	return count;
}

