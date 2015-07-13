/*
 */

#include "Pawn.hpp"

int Pawn::initScore(Board &board)
{
	return initDoubledPawns(board)+passedPawns(board)+isolatedPawn(board);
}

bool Pawn::isDoubledPawns(Board &board, int file, int color)
{
    U64 pawnsOnFile = board.getBitBoard(Move::PAWN_TYPE,color) & LookUpTables::MASK_FILE[file];
    return BitBoardUtils::countBBBitsSet(pawnsOnFile) > 1;
}

int Pawn::initDoubledPawns(Board &board)
{
	int whiteCount(0);
	int blackCount(0);
	int column;
	for (column=0; column<=7; column++)
	{
		whiteCount += isDoubledPawns(board,column,WHITE);
		blackCount += isDoubledPawns(board,column,BLACK);
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

