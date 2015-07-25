#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Color.hpp"
#include "BitBoardUtils.hpp"

namespace Pawn
{
	const static int DOUBLED_PAWN_PENALTY = -20;
	const static int ISOLATED_PAWN_PENALTY = -10;
	const static int PASSED_PAWN_BONUS = 15;

	/** Score calculation **/
	int initScore(const Board &board);
	int initDoubledPawns(const Board &board);
	int initPassedPawns(const Board &board); // TODO : take are of doubled passed pawns
	// TODO : calculate set-wise instead of pawn by pawn
	int initIsolatedPawns(const Board &board);

	/** Utils **/
    inline int countPawnsInFile(const Board &board, const int file, const int color)
    {
        return BitBoardUtils::countBBBitsSet(board.getBitBoard(Piece::PAWN_TYPE,color) & LookUpTables::MASK_FILE[file]);
    };

	inline int countPawns(const Board &board, const int color)
	{
        return BitBoardUtils::countBBBitsSet(board.getPawns(color));
    };

    inline bool hasNeighbors(const Board &board, const int file, const int color)
    {
        return (board.getPawns(color) & LookUpTables::NEIGHBOR_FILES[file]);
    };

};

#endif // Pawn_H
