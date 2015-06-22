#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Board.hpp"
#include "Utils.hpp"
#include "EvalTables.hpp"

class Eval
{
public:
    const static unsigned int TOTAL_MATERIAL = 7940;

    Eval(std::shared_ptr<Board> boardPtr);
    int evaluate();

    void init(); // Here i permute the tables to get the indexes in the right order and i fill black values
    /* These functions are called just before execute/undoMove, to keep the current colorToPlay*/
    void updateEvalAttributes(const Move &move);
    void rewindEvalAttributes(const Move &move);

    inline int getOpeningPSQValue(){return myOpeningPSQValue;};
    inline int getEndgamePSQValue(){return myEndgamePSQValue;};
    inline int getGameStage(){return myGameStage;};

private:
    std::shared_ptr<Board> myBoard;
    int myGameStage; // Total material for both sides
    int myOpeningPSQValue; // Updated after each move in evaluate
    int myEndgamePSQValue;
    int myMaterialScore

	const unsigned int KING_VALUE = 10000;
	const unsigned int QUEEN_VALUE = 900;
	const unsigned int ROOK_VALUE = 500;
	const unsigned int KNIGHT_VALUE = 310;
	const unsigned int BISHOP_VALUE = 325;
	const unsigned int PAWN_VALUE = 100;

    int getWhitePiecesValue();
    int getBlackPiecesValue();
    int getMobilityScore();
    inline int getMaterialScore(){return getWhitePiecesValue()-getBlackPiecesValue();};



};

#endif // EVAL_H_INCLUDED
