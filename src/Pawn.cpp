/*
 */

#include "Pawn.hpp"

int Pawn::getScore(Board &board)
{
	return doubledPawns(board)+passedPawns(board)+isolatedPawn(board);
}

int Pawn::doubledPawns(Board &board)
{
	int whiteCount(0);
	int blackCount(0);
	int column;
	for (column=0; column<=7; column++)
	{
		U64 pawnsOnFile = board.getWhitePawns() & LookUpTables::MASK_FILE[column];
		whiteCount += BitBoardUtils::countBBBitsSet(pawnsOnFile) > 1;
		pawnsOnFile = board.getBlackPawns() & LookUpTables::MASK_FILE[column];
		blackCount += BitBoardUtils::countBBBitsSet(pawnsOnFile) > 1;
	}
	return (whiteCount-blackCount)*DOUBLED_PAWN_PENALTY;
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

