#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Board.hpp"
#include "EvalTables.h"

class Eval
{
public:
    Eval(std::shared_ptr<Board> boardPtr);
    int evaluate();

    void init(); // Here i permute the tables to get the indexes in the right order and i fill black values

private:
    std::shared_ptr<Board> myBoard;
    int myGameStage; // 1 for midgame, 0 for endgame
    int myPSQvalue; // Updated after each move in evaluate

	const unsigned int KING_VALUE = 10000;
	const unsigned int QUEEN_VALUE = 900;
	const unsigned int ROOK_VALUE = 500;
	const unsigned int KNIGHT_VALUE = 310;
	const unsigned int BISHOP_VALUE = 325;
	const unsigned int PAWN_VALUE = 100;

    int getWhitePiecesValue();
    int getBlackPiecesValue();
    int getMobilityScore();
    inline int getMaterialScore(return getWhitePiecesValue()-getBlackPiecesValue(););


};

#endif // EVAL_H_INCLUDED
