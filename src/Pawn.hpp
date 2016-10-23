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
    
    /** Initialize Pawn table **/
    void initPawnTable();

	/** Score calculation **/
    int getScore(const Board &board, const int gameStage, const int alpha);
    int calculateEntryCount();

	int calculateScore(const Board &board, const int gameStage, const int alpha);

	/** Count Pawns of each status **/
	int doubledPawns(const Board &board);
	int passedPawns(const Board &board); // TODO : take are of doubled passed pawns
	// TODO : calculate set-wise instead of pawn by pawn
    int isolatedPawns(const Board &board);
    int supportedPawns(const Board &board);

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
};


inline std::ostream& operator<<(std::ostream &strm, const Pawn::Entry &entry) {

    strm << " > ";
    strm << entry.key << " ";
    strm << "Score " << entry.score;
	return strm;
}

#endif // Pawn_H
