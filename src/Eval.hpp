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

    /* These functions are called just before execute/undoMove, to keep the current colorToPlay*/
    void updateEvalAttributes(const Move &move);
    void rewindEvalAttributes(const Move &move);

    inline int getOpeningPSQValue(){return myOpeningPSQValue;};
    inline int getEndgamePSQValue(){return myEndgamePSQValue;};
    inline int getGameStage(){return myGameStage;};
	inline int getPawnScore(){return myPawnScore;};
    static void sortMoveList(std::vector<Move>& moveList);

private:

    const static unsigned int QUEEN_VALUE = 900;
	const static unsigned int ROOK_VALUE = 500;
    const static unsigned int KING_VALUE = 10000;
	const static unsigned int KNIGHT_VALUE = 310;
	const static unsigned int BISHOP_VALUE = 325;
	const static unsigned int PAWN_VALUE = 100;

    std::shared_ptr<Board> myBoard;
    int myGameStage; // Total material for both sides
    int myOpeningPSQValue; // Updated after each move in evaluate
    int myEndgamePSQValue;
    int myMaterialScore;
	int myPawnScore; // Updated in Pawn namespace

    void init(); // Here i permute the tables to get the indexes in the right order and i fill black values

    int getWhitePiecesValue();
    int getBlackPiecesValue();
    int getMobilityScore();
    inline int initPawnScore(){return Pawn::getScore(myBoard);}; // Calculated with namespace Pawn methods, used in init()
    inline int getMaterialScore(){return myMaterialScore;};
    static int pieceTypeToValue(int type);

};

#endif // EVAL_H_INCLUDED
