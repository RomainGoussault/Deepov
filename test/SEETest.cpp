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
#include "Board.hpp"
#include "MoveGen.hpp"



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

	SECTION("SEE")
	{
		//Take the pawn, the rook is defended
		Board board("k7/3q4/3p3Q/8/8/3R4/8/K7 w - -");
		REQUIRE(board.see(SQ_D6, BLACK) == Piece::PieceValue::PAWN_VALUE);

		//Don't take the pawn!
		board = Board("k7/3q4/3p4/8/8/3R4/8/K7 w - -");
		REQUIRE(board.see(SQ_D6, BLACK) == 0);

		// Free knight
		board = Board("k7/3q4/3n3Q/8/8/3R2B1/8/K7 w - -");
		REQUIRE(board.see(SQ_D6, BLACK) == Piece::PieceValue::KNIGHT_VALUE);

		// knight ans bishop for a rook good, trade
		board = Board("k7/2b5/3n3Q/8/8/3R4/8/K7 w - -");
		REQUIRE(board.see(SQ_D6, BLACK) == Piece::PieceValue::KNIGHT_VALUE + Piece::PieceValue::BISHOP_VALUE - Piece::PieceValue::ROOK_VALUE);

		// knight ans bishop for a rook, bad trade
		board = Board("k7/2b5/3n3Q/8/8/3Q4/8/K7 w - -");
		REQUIRE(board.see(SQ_D6, BLACK) == 0);
	}

	SECTION("SEE Move")
	{

		Board board("k7/8/2qn3Q/2P5/8/3R4/8/K7 w - -");
		MoveGen mg(board);

		auto moves = mg.getWhitePawnPseudoLegalMoves();
		auto move = moves[0];

		int seeScore = board.seeCapture(move, BLACK);
		REQUIRE(seeScore == Piece::PieceValue::KNIGHT_VALUE);
	}
}
