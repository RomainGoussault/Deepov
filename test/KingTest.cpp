#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "King.hpp"
#include "Piece.hpp"

TEST_CASE( "King moves ", "[king]" )
{
	SECTION("Random position 1")
	{
		Board board("rnbqkbnr/ppp2ppp/4p3/3p4/3P4/8/PPPKPPPP/RNBQ1BNR w kq - 0 3");
		Position position(3,1);
		PiecePtr kingPtr = board.getPiecePtr(position);

		int size = kingPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 4);
	}

	SECTION("King side castling")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		Position position(3,0);
		PiecePtr kingPtr = board.getPiecePtr(position);
		int size = kingPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 0);

		board = Board("rnbqkbnr/ppppp3/5pp1/7p/8/5NPB/PPPPPP1P/RNBQK2R w KQkq h6 0 4");
		position = Position(4,0);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 2);

		board = Board("rnbqkbnr/ppppp3/5pp1/7p/8/5NPB/PPPPPP1P/RNBQK1R1 b Qkq - 1 4");
		position = Position(4,0);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 1);

		board = Board("rnbqkbnr/ppppp3/5pp1/7p/8/5NPB/PPPPPP1P/RNBQ1K1R b kq - 1 4");
		position = Position(5,0);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 3);

		board = Board("rnb1kbnr/pppp4/4ppp1/7p/PP6/5NqB/R1PPPP1P/1NBQK2R w Kkq - 0 10");
		position = Position(4,0);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 1);

		board = Board("rnb2bnr/ppppk3/5pp1/1N2p2p/PP6/7q/R1PPPPB1/1NBQK2R w K - 2 15");
		position = Position(4,0);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 2);
	}

	SECTION("Queen side castling")
	{
		Board board("r3kbnr/pppqpppp/2n5/3p4/3P2b1/1P4P1/P1PQPP1P/RNB1KBNR w KQkq - 1 5");
		Position position(4,7);
		PiecePtr kingPtr = board.getPiecePtr(position);
		int size = kingPtr->getPseudoLegalMoves(board).size();
		REQUIRE(size == 2);

		board = Board("1r2kbnr/pppqpppp/2n5/3p4/3P2b1/PP4P1/2PQPP1P/RNB1KBNR w KQk - 1 6");
		position = Position(4,7);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 1);

		board = Board("r2k1bnr/pppqpppp/2n5/3p4/3P2b1/PP4P1/2PQPP1P/RNB1KBNR w KQ - 1 6");
		position = Position(3,7);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 2);

		board = Board("r3kbnr/pppqpppp/2n5/Q2p4/3P2b1/1P4P1/P1P1PP1P/RNB1KBNR b KQkq - 2 5");
		position = Position(4,7);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 2);

		board = Board("r3kbnr/p1pqppp1/1Qn4p/3p4/3P2b1/PP4P1/2P1PP1P/RNB1KBNR b KQkq - 0 7");
		position = Position(4,7);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 2);

		board = Board("r3kbnr/p1Qqpp2/2n3pp/3p4/3P2b1/PP4P1/2P1PP1P/RNB1KBNR b KQkq - 0 8");
		position = Position(4,7);
		kingPtr = board.getPiecePtr(position);
		size = kingPtr->getPseudoLegalMoves(board).size();
		std::cout << board;
		REQUIRE(size == 1);
	}
}
