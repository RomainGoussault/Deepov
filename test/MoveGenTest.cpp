#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Bitboard Pawn EP moves", "[pawn]" )
{
    initmagicmoves();

    SECTION("EnPassant from FEN")
    {
		FastBoard board("rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
		MoveGen moveGen(board);
		REQUIRE((board.getMovesHistory()).size() == 1); // A move is added if there is an EP square

		std::vector<FastMove> epMoves = moveGen.getBlackEnPassantMoves();
		int epSize = epMoves.size();
		REQUIRE(epSize == 1);
    }

    SECTION("EnPassant after execute move")
	{
		FastBoard board("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
		int origin = 53; // F7
		int destination = 37; // F5

		FastMove move(origin, destination, FastMove::DOUBLEPAWNPUSH_FLAG, FastMove::PAWN_TYPE);
		board.executeMove(move);
		REQUIRE((board.getMovesHistory()).size() == 1);

		boost::optional<FastMove> lastMove(board.getEnemyLastMove());
		REQUIRE(lastMove);

        MoveGen moveGen(board);
		REQUIRE((board.getMovesHistory()).size() == 1);

		std::vector<FastMove> epMoves = moveGen.getWhiteEnPassantMoves();
        int epSize = epMoves.size();
		REQUIRE(epSize == 1);
	}
}
