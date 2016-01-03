#include "catch.hpp"
#include "Board.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Zobrist key", "[zobrist]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("Test Zobrist key on quiet move")
	{
		Board board;
		MoveGen moveGen(board);

		Zkey initialKey = board.key;

		auto moves = moveGen.generateMoves();
		Move move = moves[0];

		board.executeMove(move);

		REQUIRE(initialKey != board.key);

		board.undoMove(move);

		REQUIRE(initialKey == board.key);
	}
}
