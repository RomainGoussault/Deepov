/*
 */

#include "Pawn.hpp"

int Pawn::pawnScore(const Board &board, const int gameStage, const int alpha)
{
    int doubled = doubledPawns(board);
    int passed = passedPawns(board);
    int isolated = isolatedPawns(board);

    int passedScore = passed*(EvalTables::PawnTable[OPENING][PASSED]*gameStage + EvalTables::PawnTable[ENDGAME][PASSED]*alpha);
    int doubledScore  = doubled*(EvalTables::PawnTable[OPENING][DOUBLED]*gameStage + EvalTables::PawnTable[ENDGAME][DOUBLED]*alpha);
    int isolatedScore = isolated*(EvalTables::PawnTable[OPENING][ISOLATED]*gameStage + EvalTables::PawnTable[ENDGAME][ISOLATED]*alpha);
    int score =  (passedScore + doubledScore + isolatedScore) / Eval::TOTAL_MATERIAL;

    return score;
}

int Pawn::doubledPawns(const Board &board)
{
	unsigned int whiteCount(0);
	unsigned int blackCount(0);
	unsigned int column;
	for (column=0; column<=7; column++)
	{
        unsigned int count=countPawnsInFile(board,column,WHITE);
		whiteCount += (count>1)*(count-1);
		count=countPawnsInFile(board,column,BLACK);
		blackCount += (count>1)*(count-1);
	}
	return static_cast<int>(whiteCount-blackCount);
}

int Pawn::passedPawns(const Board &board)
{
    unsigned int whiteCount(0);
	unsigned int blackCount(0);
    U64 whitePawns = board.getWhitePawns();
    U64 blackPawns = board.getBlackPawns();

    while (whitePawns)
	{
		//Getting the index of the MSB
		Square positionMsb = msb(whitePawns);
        //Removing the MSB
		whitePawns = whitePawns ^ (0 | 1LL << positionMsb);
        // Add 1 if condition is true
        whiteCount += ((Tables::PASSED_PAWN_MASK[WHITE][positionMsb] & blackPawns) == 0);
    }

    whitePawns = board.getWhitePawns(); // reloads the white pawns bitboard

    while (blackPawns)
	{
		//Getting the index of the MSB
		Square positionMsb = msb(blackPawns);
        //Removing the MSB
		blackPawns = blackPawns ^ (0 | 1LL << positionMsb);
        // Add 1 if condition is true
        blackCount += ((Tables::PASSED_PAWN_MASK[BLACK][positionMsb] & whitePawns) == 0);
    }

	return static_cast<int>(whiteCount-blackCount);
}

int Pawn::isolatedPawns(const Board &board)
{
    unsigned int whiteCount(0);
	unsigned int blackCount(0);
	unsigned int column;

	for (column=0; column<=7; column++)
	{
        unsigned int count=countPawnsInFile(board,column,WHITE);
		whiteCount += (count>0)&(!hasNeighbors(board,column,WHITE));
		count=countPawnsInFile(board,column,BLACK);
		blackCount += (count>0)&(!hasNeighbors(board,column,BLACK));
	}

	return static_cast<int>(whiteCount-blackCount);
}


