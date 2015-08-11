#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Types.hpp"
#include "BitBoardUtils.hpp"
#include "EvalTables.hpp"
#include "Eval.hpp"

namespace Pawn
{

    enum Status
    {
        PASSED = 0,
        DOUBLED = 1,
        ISOLATED = 2
    };

	/** Score calculation **/
	unsigned int pawnScore(const Board &board, const int gameStage, const int alpha);

	/** Count Pawns of each status **/
	unsigned int doubledPawns(const Board &board);
	unsigned int passedPawns(const Board &board); // TODO : take are of doubled passed pawns
	// TODO : calculate set-wise instead of pawn by pawn
	unsigned int isolatedPawns(const Board &board);

	/** Utils **/
    inline unsigned int countPawnsInFile(const Board &board, const unsigned int file, const Color color)
    {
        return BitBoardUtils::countBBBitsSet(board.getBitBoard(Piece::PAWN,color) & Tables::MASK_FILE[file]);
    };

	inline unsigned int countPawns(const Board &board, const Color color)
	{
        return BitBoardUtils::countBBBitsSet(board.getPawns(color));
    };

    inline bool hasNeighbors(const Board &board, const unsigned int file, const Color color)
    {
        return (board.getPawns(color) & Tables::NEIGHBOR_FILES[file]);
    };

};

#endif // Pawn_H
