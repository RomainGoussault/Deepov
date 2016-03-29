#include "catch.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"
#include "Eval.hpp"


TEST_CASE( "Test move rating", "[moveordering]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("8/8/3k4/4b3/2nnn3/2nQn3/2nnn3/7K w - - 0 1"));
	MoveGen moveGen(*sp);

    std::vector<Move> moveList = moveGen.generateMoves();
    
    MoveOrdering moveOrder;
    moveOrder.rateMoves(moveList);

    for (auto it=moveList.begin(); it<moveList.end(); it++)
    {
        REQUIRE(it->getMoveRating() == Piece::KNIGHT_VALUE);
    }
}


TEST_CASE( "Compare sort methods", "[moveordering]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r4rk1/ppp1nppp/2n2q2/4p1B1/1b1pP3/2NP1NPb/PPP1QPBP/2KR3R w - - 3 11"));
	MoveGen moveGen(*sp);

	std::vector<Move> moveList = moveGen.generateMoves();
    
    MoveOrdering moveOrder;
    moveOrder.rateMoves(moveList);
    moveOrder.sortMoves(moveList);

    Move bestMove=*std::begin(moveList);

    REQUIRE(bestMove.toShortString() == "g5f6");

}
