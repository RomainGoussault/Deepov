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

	const unsigned int KING_VALUE = 100;
	const unsigned int QUEEN_VALUE = 9;
	const unsigned int ROOK_VALUE = 5;
	const unsigned int KNIGHT_VALUE = 3;
	const unsigned int BISHOP_VALUE = 3;
	const unsigned int PAWN_VALUE = 1;

    int getMobilityScore();
    int getMaterialScore();

};

#endif // EVAL_H_INCLUDED
