#include "catch.hpp"
#include "Board.hpp"



TEST_CASE( "getSmallestAttacker", "[SEE]" )
{
    Tables::init();
	MagicMoves::initmagicmoves();

	SECTION("getSmallestAttacker")
	{
		Board board("k7/5q2/3n4/8/8/8/8/K7 w - -");
		U64 attackers;
		Piece::PieceType pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::NO_PIECE_TYPE);

		board = Board("k7/5q2/3n3Q/2P5/4N3/3R4/8/K7 w - -");
		attackers = 0LL;
		pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::PAWN);

		board = Board("k7/5q2/3n3Q/8/4N3/3R4/7B/K7 w - -");
		attackers = 0LL;
		pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::KNIGHT);

		board = Board("k7/5q2/3n3Q/8/8/3R4/7B/K7 w - -");
		attackers = 0LL;
		pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::BISHOP);

		board = Board("k7/5q2/3n3Q/8/8/3R4/8/K7 w - -");
		attackers = 0LL;
		pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::ROOK);

		board = Board("k7/5q2/3n3Q/8/8/8/8/K7 w - -");
		attackers = 0LL;
		pieceType = board.getSmallestAttacker(SQ_D6, BLACK, attackers);
		REQUIRE(pieceType == Piece::PieceType::QUEEN);
	}
}
