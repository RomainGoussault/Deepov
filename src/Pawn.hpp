#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Types.hpp"
#include "BitBoardUtils.hpp"
#include "EvalTables.hpp"
#include "Eval.hpp"

namespace Pawn
{

    const static int HASH_SIZE = 16384;

    enum Status
    {
        PASSED = 0,
        DOUBLED = 1,
        ISOLATED = 2
    };

    struct Entry {

        Zkey key;
        int score;

    };


	/** Score calculation **/
    int getScore(const Board &board, const int gameStage, const int alpha);
    int calculateEntryCount();

	int calculateScore(const Board &board, const int gameStage, const int alpha);

	/** Count Pawns of each status **/
	int doubledPawns(const Board &board);
	int passedPawns(const Board &board); // TODO : take are of doubled passed pawns
	// TODO : calculate set-wise instead of pawn by pawn
	int isolatedPawns(const Board &board);

	/** Utils **/
    inline unsigned int countPawnsInFile(const Board &board, const unsigned int file, const Color color)
    {
        return popcount(board.getBitBoard(Piece::PAWN,color) & Tables::MASK_FILE[file]);
    };

	inline unsigned int countPawns(const Board &board, const Color color)
	{
        return popcount(board.getPawns(color));
    };

    inline bool hasNeighbors(const Board &board, const unsigned int file, const Color color)
    {
        return (board.getPawns(color) & Tables::NEIGHBOR_FILES[file]);
    };

    //extern Entry pawnsTable[HASH_SIZE];


};

#endif // Pawn_H
