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

	SECTION( "Test Zobrist key on castling move" )
	{
		Board board("rnbqkbnr/1pppp1pp/p4p2/8/2B5/3N4/PPPPPPPP/RNBQK2R w KQkq -");
		MoveGen moveGen(board);

		auto moves = moveGen.getKingPseudoLegalMoves(WHITE);
		REQUIRE(moves.size() == 2);

		//find castling move
		Move castlingMove = moves[0].isCastling() ? moves[0] : moves[1];
		REQUIRE(castlingMove.isCastling());

		Zkey initialKey = board.key;

		board.executeMove(castlingMove);
		REQUIRE(initialKey != board.key);

		board.undoMove(castlingMove);
		REQUIRE(initialKey == board.key);
	}

	SECTION( "Test Zobrist key on capture move" )
	{
		Board board("1nbqkbRr/1pppp2p/p4p2/6p1/1PB5/3N4/P1PPPPPP/R1BQK3 b KQkq -");
		MoveGen moveGen(board);

		auto moves = moveGen.getRookPseudoLegalMoves(BLACK);
		REQUIRE(moves.size() == 1);

		//find castling move
		Move captureMove = moves[0];
		REQUIRE(captureMove.isCapture());

		Zkey initialKey = board.key;

		board.executeMove(captureMove);
		REQUIRE(initialKey != board.key);

		board.undoMove(captureMove);
		REQUIRE(initialKey == board.key);
	}

	SECTION( "Test Zobrist key on perft Kiwipete" )
	{
		Tables::init();
		MagicMoves::initmagicmoves();
		Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
		Zkey initialKey = board.key;

		board.perft(3);
		REQUIRE(initialKey == board.key);
	}
}
