#include "catch.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"


TEST_CASE( "Compare sort methods&", "[moveordering]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r4rk1/ppp1nppp/2n2q2/4p1B1/1b1pP3/2NP1NPb/PPP1QPBP/2KR3R w - - 3 11"));
	MoveGen moveGen(*sp);

	std::vector<Move> moveList1 = moveGen.generateMoves();

    MoveOrdering::rateMoves(moveList1);
    MoveOrdering::sortMoves(moveList1);

    std::cout << "MoveOrdering::sortMoves" << std::endl;
    std::cout << *std::begin(moveList1) << std::endl;

	std::vector<Move> moveList2 = moveGen.generateMoves();
    Eval::sortMoveList(moveList2);
    Move bestMove=*std::begin(moveList2);
    std::cout << "Eval::sortMoveList" << std::endl;
    std::cout << bestMove << std::endl;

    REQUIRE(bestMove.toShortString() == "g5f6");

}
