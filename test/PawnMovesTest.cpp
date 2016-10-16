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


TEST_CASE( "Pawn moves", "[pawn]" )
{
	Tables::init();

	SECTION("starting position")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		unsigned int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 8*2);
		REQUIRE(blackSize == 8*2);
	}

	SECTION("4 moves test")
	{
		Board board("8/8/8/8/8/2q1r3/3P4/8 w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 4);
	}

	SECTION("blocked pawns")
	{
		Board board("8/8/1p2p3/qqq1r3/8/8/3P4/1q6 w - -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getWhitePawnPseudoLegalMoves().size();
		unsigned int blackSize = moveGen.getBlackPawnPseudoLegalMoves().size();
		REQUIRE(whiteSize == 2);
		REQUIRE(blackSize == 0);
	}
}

TEST_CASE( "Pawn en passant with check", "[pawn]" )
{
	Tables::init();
	MagicMoves::initmagicmoves();


	SECTION("Pawn en passant with check")
	{
		Board board("8/p1pR1p1p/8/2k3P1/2p1KN2/1r6/6P1/8 b - -");

		//Move 1
		MoveGen movegen(board);
		std::vector<Move> moves(movegen.generateMoves());
		Move movePawn;

		//Find double push black move
		for(auto move : moves)
		{
			if(move.getDestination() == SQ_F5)
			{
				movePawn = move;
			}
		}

		board.executeMove(movePawn);


		//Move 2
		movegen = MoveGen(board);
		moves = movegen.generateMoves();
		bool isEpMoveExist = false;

		//Find EP white move
		for(auto move : moves)
		{
			if(move.getOrigin() == SQ_G5)
			{
				isEpMoveExist = true;
			}
		}

		REQUIRE(isEpMoveExist == true);
	}
}

TEST_CASE( "Pawn promotions", "[pawn]" )
{
	Tables::init();

	SECTION("Promotion")
	{
		Board board("8/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
		MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 4);
	}

	SECTION("Promotion with capture")
	{
		Board board("1r6/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
		MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 8);

		U64 pawnBitboard = board.getWhitePawns();

		Move promotionCapture(static_cast<Square>(50),static_cast<Square>(57),Move::PROMOTION_FLAG + Move::CAPTURE_FLAG, Piece::PAWN);
		promotionCapture.setCapturedPieceType(Piece::ROOK);

		board.executeMove(promotionCapture);
		REQUIRE(pawnBitboard != board.getWhitePawns());

		board.undoMove(promotionCapture);
		REQUIRE(pawnBitboard == board.getWhitePawns());
	}

	SECTION("Promotion with double capture")
	{
		Board board("3r1r2/4P3/8/k7/8/8/8/1K6 w - - 0 1");
		MoveGen moveGen(board);
		unsigned int size = moveGen.getWhitePawnPseudoLegalMoves().size();
		REQUIRE(size == 12);
	}
}
