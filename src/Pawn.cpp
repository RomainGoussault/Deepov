/*
 */

#include "Pawn.hpp"

int Pawn::initScore(Board &board)
{
	return initDoubledPawns(board)+passedPawns(board)+isolatedPawn(board);
}

int Pawn::isDoubledPawns(Board &board, int file, int color)
{
    U64 pawnsOnFile = board.getWhitePawns() & LookUpTables::MASK_FILE[column];
}

int Pawn::initDoubledPawns(Board &board)
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
	if (color == WHITE)
	{
		return BitBoardUtils::countBBBitsSet(board.getWhitePawns());
	}
	else
	{
		return BitBoardUtils::countBBBitsSet(board.getBlackPawns());
	}
}

