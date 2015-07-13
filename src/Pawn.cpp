/*
 */

#include "Pawn.hpp"

int Pawn::initScore(Board &board)
{
	return initDoubledPawns(board)+passedPawns(board)+isolatedPawn(board);
}

int Pawn::countPawnsInFile(Board &board, int file, int color)
{
    U64 pawnsOnFile = board.getBitBoard(Move::PAWN_TYPE,color) & LookUpTables::MASK_FILE[file];
    return BitBoardUtils::countBBBitsSet(pawnsOnFile);
}

int Pawn::initDoubledPawns(Board &board)
{
	int whiteCount(0);
	int blackCount(0);
	int column;
	for (column=0; column<=7; column++)
	{
        int count=countPawnsInFile(board,column,WHITE);
		whiteCount += (count>1)*(count-1);
		count=countPawnsInFile(board,column,BLACK);
		blackCount += (count>1)*(count-1);
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

