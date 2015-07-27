#ifndef Pawn_H
#define Pawn_H


#include "Board.hpp"
#include "Color.hpp"
#include "BitBoardUtils.hpp"

namespace Pawn
{
	const static unsigned int DOUBLED_PAWN_PENALTY = -20;
	const static unsigned int ISOLATED_PAWN_PENALTY = -10;
	const static unsigned int PASSED_PAWN_BONUS = 15;

	/** Score calculation **/
	unsigned int initScore(const Board &board);
	unsigned int initDoubledPawns(const Board &board);
	unsigned int initPassedPawns(const Board &board); // TODO : take are of doubled passed pawns
	// TODO : calculate set-wise instead of pawn by pawn
	unsigned int initIsolatedPawns(const Board &board);

	/** Utils **/
    inline unsigned int countPawnsInFile(const Board &board, const unsigned int file, const Color color)
    {
        return BitBoardUtils::countBBBitsSet(board.getBitBoard(Piece::PAWN_TYPE,color) & Tables::MASK_FILE[file]);
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
