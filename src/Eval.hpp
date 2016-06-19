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

#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Board.hpp"
#include "Utils.hpp"
#include "BitBoardUtils.hpp"
#include "EvalTables.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"

class Eval
{
public:
    const static int TOTAL_MATERIAL = 2*Piece::QUEEN_VALUE + 4*Piece::ROOK_VALUE +
    4*Piece::BISHOP_VALUE + 4*Piece::KNIGHT_VALUE + 16*Piece::PAWN_VALUE;
    const static int DRAW_SCORE = 0;
    const static int CHECKMATE_SCORE = 100000;

    static int POSITIONNAL_GAIN_PERCENT;
    static int PAWN_GAIN_PERCENT;
	static int MOBILITY_GAIN_PERCENT;

    Eval(std::shared_ptr<Board> boardPtr);
    int evaluate();

    /* These functions are called just before execute/undoMove, to keep the current colorToPlay*/
    void updateEvalAttributes(const Move &move);
    void rewindEvalAttributes(const Move &move);

    /* Functions that calculate eval parameters */
    int calcMobilityScore(const int64_t alpha) const; // alpha is TOTAL_MATERIAL-myGameStage
    int calcMaterialAdjustments(const int64_t alpha) const; // material evaluations that are not updated at each move

    /* These functions are mainly for tests */
    inline int getOpeningPSQValue() const {return myOpeningPSQValue;};
    inline int getEndgamePSQValue()const {return myEndgamePSQValue;};
    inline int64_t getGameStage() const {return myGameStage;};
	inline int getMaterialScore() const {return myMaterialScore;};

    int getWhitePiecesValue() const;
    int getBlackPiecesValue() const;

    /* Move ordering */
	static void sortMoveList(std::vector<Move>& moveList);
    static int pieceTypeToValue(int type);

private:

    std::shared_ptr<Board> myBoard;
    int64_t myGameStage; // Total material for both sides
    int myOpeningPSQValue; // Updated after each move in evaluate
    int myEndgamePSQValue;
    int myMaterialScore;

    void init(); // Here i permute the tables to get the indexes in the right order and i fill black values
	int calculateKingSafety();
};

#endif // EVAL_H_INCLUDED
