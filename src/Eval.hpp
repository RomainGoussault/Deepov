#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "Board.hpp"

class Eval
{
public:

    Eval(std::shared_ptr<Board> boardPtr);
    int evaluate();

private:
    std::shared_ptr<Board> myBoard;

	const unsigned int KING_VALUE = 10000;
	const unsigned int QUEEN_VALUE = 900;
	const unsigned int ROOK_VALUE = 500;
	const unsigned int KNIGHT_VALUE = 310;
	const unsigned int BISHOP_VALUE = 325;
	const unsigned int PAWN_VALUE = 100;

    int getMobilityScore();
    int getMaterialScore();

};

#endif // EVAL_H_INCLUDED
