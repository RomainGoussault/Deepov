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
#include "MagicMoves.hpp"
#include "MoveGen.hpp"

TEST_CASE( "Movegen" )
{
    Tables::init();
	Board board;
	MoveGen moveGen(board);

	std::vector<Move> moveList = moveGen.getWhitePawnPseudoLegalMoves();
	REQUIRE(moveList.size() == 16);

	moveList = moveGen.getKingPseudoLegalMoves(WHITE);
	REQUIRE(moveList.size() == 0);

	moveList = moveGen.getKnightPseudoLegalMoves(WHITE);
	REQUIRE(moveList.size() == 4);
}

TEST_CASE( "Bitboard Pawn EP moves", "[pawn]" )
{
    MagicMoves::initmagicmoves();
    Tables::init();

    SECTION("EnPassant from FEN")
    {
		Board board("rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
		MoveGen moveGen(board);
		REQUIRE((board.getMovesHistory()).size() == 1); // A move is added if there is an EP square

		std::vector<Move> epMoves;
		moveGen.appendBlackEnPassantMoves(epMoves);
		unsigned int epSize = epMoves.size();
		REQUIRE(epSize == 1);
    }

    SECTION("EnPassant after execute/undo move")
	{
    	std::shared_ptr<Board> boardPtr = std::make_shared<Board>("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
        MoveGen moveGen(boardPtr);
		Square origin = SQ_F7; // F7
		Square destination = SQ_F5; // F5

		Move move(origin, destination, Move::DOUBLE_PAWN_PUSH_FLAG, Piece::PAWN);
		boardPtr->executeMove(move);
		REQUIRE((boardPtr->getMovesHistory()).size() == 1);

		const Move* lastMove(boardPtr->getEnemyLastMove());
		REQUIRE(lastMove);

		REQUIRE((boardPtr->getMovesHistory()).size() == 1);

		std::vector<Move> epMoves;
		moveGen.appendWhiteEnPassantMoves(epMoves);
		unsigned int epSize = epMoves.size();
		REQUIRE(epSize == 1);

		boardPtr->executeMove(epMoves[0]);

        boardPtr->undoMove(epMoves[0]);

        //TODO: Test something maybe?
        //Call me maybe?
	}
}

TEST_CASE( "Castling" )
{
    Tables::init();
	SECTION("Castling possible")
	{
		Board board("r3k2r/pppppppp/8/2nqn3/1NBQ1N2/8/PPPPPPPP/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == true);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == true);
	}

	SECTION("Castling not possible because pieces are in the middle")
	{
		Board board("r2nkq1r/pppppppp/8/2B5/3Q4/8/PPPPPPPP/RN2K1NR w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == false);
	}

	SECTION("Castling not possible because pieces attacking")
	{
		Board board("r3k2r/pp1ppppp/4nqN1/N7/1P1Q1N2/b3rP1P/P1RP1PP1/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == false);
	}

	SECTION("Random castling test")
	{
		Board board("r3k2r/Q3ppp1/4n3/Nppp2pR/1RP3P1/b3q1rP/P3N3/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == true);
	}
}
