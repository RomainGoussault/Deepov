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
#include "BitBoardUtils.hpp"
#include "MagicMoves.hpp"
#include "Tables.hpp"
#include "MoveGen.hpp"
#include "Types.hpp"
#include "Piece.hpp"


TEST_CASE( "Zobrist key", "[zobrist]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();	
	ZK::initZobristKeys();

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


	SECTION( "Test Zobrist key for castling rights" )
	{
		Board board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq -");
		Zkey initialKey = board.key;

        Move move1 = Move(Square::SQ_E1, Square::SQ_E2, 0, Piece::PieceType::KING);
        Move move2 = Move(Square::SQ_E8, Square::SQ_E7, 0, Piece::PieceType::KING);
        Move move3 = Move(Square::SQ_E2, Square::SQ_E1, 0, Piece::PieceType::KING);
        Move move4 = Move(Square::SQ_E7, Square::SQ_E8, 0, Piece::PieceType::KING);


		board.executeMove(move1);
		REQUIRE(initialKey != board.key);

		board.executeMove(move2);
		board.executeMove(move3);
		board.executeMove(move4);

		REQUIRE(initialKey != board.key);

		board.undoMove(move4);
		board.undoMove(move3);
		board.undoMove(move2);
		board.undoMove(move1);

		REQUIRE(initialKey == board.key);

	}


	SECTION( "Test Zobrist key for color to play" )
	{
		Board board("r3k2r/8/8/8/8/8/8/R3K2R w KQkq -");
		Zkey initialKey = board.key;

        Move move1 = Move(Square::SQ_E1, Square::SQ_E2, 0, Piece::PieceType::KING);
        Move move2 = Move(Square::SQ_E8, Square::SQ_E7, 0, Piece::PieceType::KING);
        Move move4 = Move(Square::SQ_E7, Square::SQ_E8, 0, Piece::PieceType::KING);
        Move move5 = Move(Square::SQ_E2, Square::SQ_F2, 0, Piece::PieceType::KING);
        Move move6 = Move(Square::SQ_F2, Square::SQ_E1, 0, Piece::PieceType::KING);


		board.executeMove(move1);
		REQUIRE(initialKey != board.key);

		board.executeMove(move2);
		board.executeMove(move5);
		board.executeMove(move4);
		board.executeMove(move6);

		REQUIRE(initialKey != board.key);

		board.undoMove(move6);
		board.undoMove(move4);
		board.undoMove(move5);
		board.undoMove(move2);
		board.undoMove(move1);

		REQUIRE(initialKey == board.key);

	}

	SECTION( "Test Zobrist key for ep square" )
	{
		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("rnbqkb1r/pp1ppppp/5n2/2pP4/8/8/PPP1PPPP/RNBQKBNR w KQkq c6 0 3"));
		Zkey initialKey = sp->key;
        REQUIRE(sp->getLastEpSquare() == SQ_C6);

        Move move1 = Move(Square::SQ_G1, Square::SQ_F3, Move::QUIET_FLAG, Piece::PieceType::KNIGHT);
        Move move2 = Move(Square::SQ_B8, Square::SQ_C6, Move::QUIET_FLAG, Piece::PieceType::KNIGHT);
        Move move3 = Move(Square::SQ_F3, Square::SQ_G1, Move::QUIET_FLAG, Piece::PieceType::KNIGHT);
        Move move4 = Move(Square::SQ_C6, Square::SQ_B8, Move::QUIET_FLAG, Piece::PieceType::KNIGHT);

		sp->executeMove(move1);
		REQUIRE(initialKey != sp->key);
        REQUIRE(sp->getLastEpSquare() == SQ_NONE);

		sp->executeMove(move2);
		sp->executeMove(move3);
		sp->executeMove(move4);

		REQUIRE(initialKey != sp->key);
        REQUIRE(sp->getLastEpSquare() == SQ_NONE);

		sp->undoMove(move4);
		sp->undoMove(move3);
		sp->undoMove(move2);
		sp->undoMove(move1);

		REQUIRE(initialKey == sp->key);
        REQUIRE(sp->getLastEpSquare() == SQ_C6);

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
