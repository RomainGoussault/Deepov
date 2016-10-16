/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "catch.hpp"
#include "Move.hpp"
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Constructor and methods" )
{
    Square origin = static_cast<Square>(4);
    Square destination = static_cast<Square>(5);
    unsigned int flags = 6;
    Piece::PieceType pieceType = Piece::BISHOP;
    Move move(origin, destination, flags, pieceType);

    REQUIRE(move.getOrigin() == origin);
    REQUIRE(move.getDestination() == destination);
    REQUIRE(move.getFlags() == flags);
    REQUIRE(move.getPieceType() == pieceType);

    move.setDestination(static_cast<Square>(3));
    move.setOrigin(static_cast<Square>(22));
    move.setFlags(0b1000);

    REQUIRE(move.getOrigin() == static_cast<Square>(22));
    REQUIRE(move.getDestination() == static_cast<Square>(3));
    REQUIRE(move.getFlags() == static_cast<Square>(8));
}

TEST_CASE( "is capture" )
{
	MagicMoves::initmagicmoves();
    Tables::init();
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
    Tables::init();
	Board fb = Board("8/8/8/8/8/8/2Q5/N7 w - -");
	MoveGen moveGen(fb);

	U64 bb = fb.getWhiteKnights();

    REQUIRE(BitBoardUtils::isBitSet(bb, 0, 0) == true);
    REQUIRE(BitBoardUtils::isBitSet(bb, 1, 2) == false);

	unsigned int size = moveGen.getKnightPseudoLegalMoves(WHITE).size();
    REQUIRE(size == 1);

	Move move = moveGen.getKnightPseudoLegalMoves(WHITE)[0];
	fb.executeMove(move);
	bb = fb.getWhiteKnights();

    REQUIRE(BitBoardUtils::isBitSet(bb, 0, 0) == false);
    REQUIRE(BitBoardUtils::isBitSet(bb, 1, 2) == true);
}

TEST_CASE( "undo Move" )
{
	MagicMoves::initmagicmoves();
    Tables::init();
	Board fb = Board("8/8/8/8/8/8/6bn/5qr1 b - -");
	MoveGen moveGen(fb);

	unsigned int size = moveGen.getRookPseudoLegalMoves(BLACK).size();
    REQUIRE(size == 1);

	U64 bb = fb.getBlackRooks();
    REQUIRE(BitBoardUtils::isBitSet(bb, 6, 0) == true);
    REQUIRE(BitBoardUtils::isBitSet(bb, 7, 0) == false);

	Move move = moveGen.getRookPseudoLegalMoves(BLACK)[0];
	fb.executeMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(BitBoardUtils::isBitSet(bb, 6, 0) == false);
    REQUIRE(BitBoardUtils::isBitSet(bb, 7, 0) == true);

	fb.undoMove(move);

	bb = fb.getBlackRooks();
    REQUIRE(BitBoardUtils::isBitSet(bb, 6, 0) == true);
    REQUIRE(BitBoardUtils::isBitSet(bb, 7, 0) == false);
}
