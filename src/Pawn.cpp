/*
 */

#include "Pawn.hpp"

unsigned int Pawn::pawnScore(const Board &board, const int64_t gameStage, const int64_t alpha)
{
    unsigned int doubled = doubledPawns(board);
    unsigned int passed = passedPawns(board);
    unsigned int isolated = isolatedPawns(board);
	return passed*(PawnTable[OPENING][0]*gameStage+PawnTable[ENDGAME][0]*alpha) +
	doubled*(PawnTable[OPENING][1]*gameStage+PawnTable[ENDGAME][1]*alpha) +
	isolated*((PawnTable[OPENING][2]*gameStage+PawnTable[ENDGAME][2]*alpha));
}

unsigned int Pawn::doubledPawns(const Board &board)
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
	return whiteCount-blackCount;
}

unsigned int Pawn::passedPawns(const Board &board)
{
    unsigned int whiteCount(0);
	unsigned int blackCount(0);
    U64 whitePawns = board.getWhitePawns();
    U64 blackPawns = board.getBlackPawns();

    while (whitePawns)
	{
		//Getting the index of the MSB
		Square positionMsb = BitBoardUtils::getMsbIndex(whitePawns);
        //Removing the MSB
		whitePawns = whitePawns ^ (0 | 1LL << positionMsb);
        // Add 1 if condition is true
        whiteCount += ((Tables::PASSED_PAWN_MASK[WHITE][positionMsb] & blackPawns) == 0);
    }

    whitePawns = board.getWhitePawns(); // reloads the white pawns bitboard

    while (blackPawns)
	{
		//Getting the index of the MSB
		Square positionMsb = BitBoardUtils::getMsbIndex(blackPawns);
        //Removing the MSB
		blackPawns = blackPawns ^ (0 | 1LL << positionMsb);
        // Add 1 if condition is true
        blackCount += ((Tables::PASSED_PAWN_MASK[BLACK][positionMsb] & whitePawns) == 0);
    }

	return whiteCount-blackCount;
}

unsigned int Pawn::isolatedPawns(const Board &board)
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

	return whiteCount-blackCount;
}


