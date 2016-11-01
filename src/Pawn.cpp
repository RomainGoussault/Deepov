/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Pawn.hpp"

Pawn::Entry pawnsTable[Pawn::HASH_SIZE];

void Pawn::initPawnTable()
{
    for(U64 i=0; i<Pawn::HASH_SIZE; i++)
    {
    	pawnsTable[i].key = 0;
    	pawnsTable[i].score = 0;
    }
}

int Pawn::getScore(const Board &board, const int gameStage, const int alpha)
{
    //Probe pawn hash first
    Zkey key = board.pawnsKey;
    int index = key % Pawn::HASH_SIZE;

    if(pawnsTable[index].key == key)
    {
        //it's a match
        return pawnsTable[index].score;
    }
    else
    {
        //calculate score and set a new entry in TT
        int score = calculateScore(board, gameStage, alpha);
        pawnsTable[index].key = key;
        pawnsTable[index].score = score;

        return score;
    }
}

int Pawn::calculateEntryCount()
{
	int count = 0;
	for(int i=0; i<HASH_SIZE; i++)
	{
		Pawn::Entry entry = pawnsTable[i];
		if(entry.key !=0)
		{
			count++;
		}
	}

	return count;
}

int Pawn::calculateScore(const Board &board, const int gameStage, const int alpha)
{
    int doubled = doubledPawns(board);
    int passed = passedPawns(board);
    int isolated = isolatedPawns(board);
    //int supported = supportedPawns(board);

    int passedScore = passed*(EvalTables::PawnTable[OPENING][PASSED]*gameStage + EvalTables::PawnTable[ENDGAME][PASSED]*alpha);
    int doubledScore  = doubled*(EvalTables::PawnTable[OPENING][DOUBLED]*gameStage + EvalTables::PawnTable[ENDGAME][DOUBLED]*alpha);
    int isolatedScore = isolated*(EvalTables::PawnTable[OPENING][ISOLATED]*gameStage + EvalTables::PawnTable[ENDGAME][ISOLATED]*alpha);
    //int supportedScore = supported*30; //TODO Deepov Tuning
    int score =  (passedScore + doubledScore + isolatedScore) / Eval::TOTAL_MATERIAL;

    return score;
}

int Pawn::supportedPawns(const Board &board)
{
    unsigned int whiteCount(0);
    unsigned int blackCount(0);
    U64 whitePawns = board.getWhitePawns();
    U64 blackPawns = board.getBlackPawns();

    while (whitePawns)
    {
        Square sq = pop_lsb(&whitePawns);
        Rank rank = getRank(sq);
        File file = getFile(sq);

        bool hasNeighbours = board.getWhitePawns() & Tables::NEIGHBOR_FILES[file];
        whiteCount += hasNeighbours && (Tables::MASK_RANK[rank-1] & board.getWhitePawns());
    }

    while (blackPawns)
    {
        Square sq = pop_lsb(&blackPawns);
        Rank rank = getRank(sq);
        File file = getFile(sq);

        bool hasNeighbours = board.getBlackPawns() & Tables::NEIGHBOR_FILES[file];
        blackCount += hasNeighbours && (Tables::MASK_RANK[rank+1] & board.getBlackPawns());
    }

    return static_cast<int>(whiteCount-blackCount);
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
		Square positionMsb = pop_lsb(&whitePawns);
        // Add 1 if condition is true
        whiteCount += ((Tables::PASSED_PAWN_MASK[WHITE][positionMsb] & blackPawns) == 0);
    }

    whitePawns = board.getWhitePawns(); // reloads the white pawns bitboard

    while (blackPawns)
	{
		//Getting the index of the MSB
		Square positionMsb = pop_lsb(&blackPawns);
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


