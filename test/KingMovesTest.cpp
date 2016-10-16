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
#include "MagicMoves.hpp"
#include <bitset>


TEST_CASE( "King moves", "[king]" )
{
	Tables::init();

	SECTION("Test pseudo-legal moves")
	{
		Board board("rnbq1b1r/ppp1np1p/4p1p1/3p2k1/3P2P1/8/PPPKPP1P/RNBQ1BNR w kq -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 4);
		REQUIRE(blackSize == 7);
	}
}

TEST_CASE( "KingCastling1", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("Test Castling 1")
	{
		Board board("1nbqk2r/pppp1ppp/8/2p1bn2/5N2/1B1Q4/P1rPPPPP/R3K2R w KQkq -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 3);
		REQUIRE(blackSize == 3);
		REQUIRE(board.hasBlackCastled() == false);
		REQUIRE(board.hasWhiteCastled() == false);
	}

	SECTION("Test Castling 2")
	{
		Board board("r3k2r/pppp1ppp/8/4b1n1/1n1NQbN1/3BB3/PPPPPPPP/R3K2R w k -");
		MoveGen moveGen(board);

		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(blackSize == 4);
		REQUIRE(whiteSize == 2);
	}
}

TEST_CASE( "CastlingRights", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	Board board("r3k2r/8/8/8/3B4/8/8/R3K2R w KQkq - 0 1");


	SECTION("Test 1 Castling")
	{
		MoveGen moveGen(board);
		unsigned int whiteSize = moveGen.getKingPseudoLegalMoves(WHITE).size();
		unsigned int blackSize = moveGen.getKingPseudoLegalMoves(BLACK).size();
		REQUIRE(whiteSize == 7);
		REQUIRE(blackSize == 7);
	}

	SECTION("Test 2 King move")
	{
		Move whiteKingMove(static_cast<Square>(4),static_cast<Square>(5),0,Piece::KING);
		board.executeMove(whiteKingMove);
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 0);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 0);
		board.undoMove(whiteKingMove);
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
	}

	SECTION("Test 3 Rook Move")
	{
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		Move whiteRookMove(static_cast<Square>(0),static_cast<Square>(16),0,Piece::ROOK);
		board.executeMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 0);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		board.undoMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}

	SECTION("Test 3 Rook Move2")
	{
		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		Move whiteRookMove(static_cast<Square>(7),static_cast<Square>(23),0,Piece::ROOK);
		board.executeMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == true);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == false);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);

		board.undoMove(whiteRookMove);

		REQUIRE(board.isQueenSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE) == 1);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}

	SECTION("Test 4 Rook Capture")
	{
		Move captureMove(static_cast<Square>(27),static_cast<Square>(63),Move::CAPTURE_FLAG,Piece::BISHOP);
		captureMove.setCapturedPieceType(Piece::ROOK);

		board.executeMove(captureMove);

		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 0);

		board.undoMove(captureMove);

		REQUIRE(board.isQueenSideCastlingAllowed(BLACK) == 1);
		REQUIRE(board.isKingSideCastlingAllowed(BLACK) == 1);
	}
}

TEST_CASE( "King castling execude/undo move", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("White castling")
	{
		Board board("r3kbnr/p2ppppp/nppqb3/4B3/8/5P2/PPPPPNPP/RNBQK2R w KQkq -");
		MoveGen moveGen(board);
		REQUIRE(board.hasWhiteCastled() == false);
		REQUIRE(board.isKingSideCastlingAllowed(WHITE));

		auto moves = moveGen.getKingPseudoLegalMoves(WHITE);
		Move castlingMove;

		for(auto move : moves)
		{
			if(move.isCastling())
			{
				castlingMove = move;
			}
		}

		board.executeMove(castlingMove);
		REQUIRE(board.hasWhiteCastled() == true);

		board.undoMove(castlingMove);
		REQUIRE(board.hasWhiteCastled() == false);
	}

	SECTION("Black castling")
	{
		Board board("r3kbnr/p2ppppp/nppqb3/4B3/8/5P2/PPPPPNPP/RNBQK2R b KQkq -");
		MoveGen moveGen(board);
		REQUIRE(board.hasBlackCastled() == false);
		REQUIRE(board.isQueenSideCastlingAllowed(BLACK));

		auto moves = moveGen.getKingPseudoLegalMoves(BLACK);
		Move castlingMove;

		for(auto move : moves)
		{
			if(move.isCastling())
			{
				castlingMove = move;
			}
		}

		board.executeMove(castlingMove);
		REQUIRE(board.hasBlackCastled() == true);

		board.undoMove(castlingMove);
		REQUIRE(board.hasBlackCastled() == false);
	}

}
TEST_CASE( "Evasion", "[king]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	SECTION("Evasion vs one rook")
	{
		Board board("8/3r4/8/8/8/3K4/8/8 w - -");
		MoveGen moveGen(board);

		auto whiteSize = moveGen.generateLegalMoves().size();
		REQUIRE(whiteSize == 6);
	}

	SECTION("Evasion vs two rooks")
	{
		Board board("k7/3rr3/8/8/8/3K4/8/8 w - -");
		MoveGen moveGen(board);

		auto whiteSize = moveGen.generateLegalMoves().size();
		REQUIRE(whiteSize == 3);
	}


	SECTION("Evasion vs one knight")
	{
		Board board("K7/8/8/8/8/2N5/8/1k6 b - -");
		MoveGen moveGen(board);

		auto size = moveGen.generateLegalMoves().size();
		REQUIRE(size == 4);
	}

	SECTION("Evasion vs one rook + one rook ally")
	{
		Board board("k7/3r4/8/7R/8/3K4/8/8 w - -");
		MoveGen moveGen(board);

		auto whiteSize = moveGen.generateLegalMoves().size();
		REQUIRE(whiteSize == 7);
	}

	SECTION("Evasion vs one rook + one bishop ally ")
	{
		Board board("k7/8/8/8/3r4/3KB3/8/8 w - -");
		MoveGen moveGen(board);

		auto whiteSize = moveGen.generateLegalMoves().size();
		REQUIRE(whiteSize == 5);
	}
}
