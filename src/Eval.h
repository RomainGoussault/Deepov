#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

class Eval
{
public:
    static int evaluate();
private:

	const unsigned int KING_VALUE = 100;
	const unsigned int QUEEN_VALUE = 9;
	const unsigned int ROOK_VALUE = 5;
	const unsigned int KNIGHT_VALUE = 3;
	const unsigned int BISHOP_VALUE = 3;
	const unsigned int PAWN_VALUE = 1;


    std::shared_ptr<FastBoard> myBoard;

    int getMobilityScore();
    int getMaterialScore();

};

#endif // EVAL_H_INCLUDED
