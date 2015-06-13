#include "catch.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Constructor and methods" )
{
    unsigned int origin = 4;
    unsigned int destination = 5;
    unsigned int flags = 6;
    unsigned int pieceType = 3;
    Move move(origin, destination, flags, pieceType);

    REQUIRE(move.getOrigin() == origin);
    REQUIRE(move.getDestination() == destination);
    REQUIRE(move.getFlags() == flags);
    REQUIRE(move.getPieceType() == pieceType);

    move.setDestination(3);
    move.setOrigin(22);
    move.setFlags(0b1000);

    REQUIRE(move.getOrigin() == 22);
    REQUIRE(move.getDestination() == 3);
    REQUIRE(move.getFlags() == 8);
}

TEST_CASE( "is capture" )
{
	MagicMoves::initmagicmoves();

	Board board("8/8/3k4/8/8/8/n4K2/rR6 b - -");
	MoveGen moveGen(board);

	Move move = moveGen.getRookPseudoLegalMoves(BLACK)[0];
    REQUIRE(move.isCapture() == true);

	move = moveGen.getKnightPseudoLegalMoves(BLACK)[0];
    REQUIRE(move.isCapture() == false);
}

TEST_CASE( "execute Move" )
{
	MagicMoves::initmagicmoves();

	Board fb = Board("8/8/8/8/8/8/2Q5/N7 w - -");
	MoveGen moveGen(fb);

	U64 bb = fb.getWhiteKnights();

    REQUIRE(Board::isBitSet(bb, 0, 0) == true);
    REQUIRE(Board::isBitSet(bb, 1, 2) == false);

	int size = moveGen.getKnightPseudoLegalMoves(WHITE).size();
    REQUIRE(size == 1);

	Move move = moveGen.getKnightPseudoLegalMoves(WHITE)[0];
	fb.executeMove(move);
	bb = fb.getWhiteKnights();

    REQUIRE(Board::isBitSet(bb, 0, 0) == false);
    REQUIRE(Board::isBitSet(bb, 1, 2) == true);
}

TEST_CASE( "undo Move" )
{
	MagicMoves::initmagicmoves();

	Board fb = Board("8/8/8/8/8/8/6bn/5qr1 b - -");
	MoveGen moveGen(fb);

	int size = moveGen.getRookPseudoLegalMoves(BLACK).size();
    REQUIRE(size == 1);

	U64 bb = fb.getBlackRooks();
    REQUIRE(Board::isBitSet(bb, 6, 0) == true);
    REQUIRE(Board::isBitSet(bb, 7, 0) == false);

	Move move = moveGen.getRookPseudoLegalMoves(BLACK)[0];
	fb.executeMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(Board::isBitSet(bb, 6, 0) == false);
    REQUIRE(Board::isBitSet(bb, 7, 0) == true);

	fb.undoMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(Board::isBitSet(bb, 6, 0) == true);
    REQUIRE(Board::isBitSet(bb, 7, 0) == false);
}
