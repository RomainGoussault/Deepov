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
#include "Pawn.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"


TEST_CASE("Pawn structure")
{
	Tables::init();	
	ZK::initZobristKeys();
	
	SECTION("Initial Position")
	{
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        REQUIRE(Pawn::doubledPawns(board) == 0);
        REQUIRE(Pawn::countPawns(board,WHITE) == 8);
        REQUIRE(Pawn::calculateScore(board,Eval::TOTAL_MATERIAL,0) == 0);
    }

	SECTION("Doubled Pawns")
	{
        Board board("rnbqkbnr/ppppppp1/p7/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        REQUIRE(Pawn::countPawnsInFile(board,0,BLACK) == 2);
        REQUIRE(Pawn::countPawnsInFile(board,3,BLACK) == 1);
        REQUIRE(Pawn::countPawnsInFile(board,7,BLACK) == 0);
        REQUIRE(Pawn::countPawns(board,BLACK) == 8);

        int gameStage = Eval::TOTAL_MATERIAL;
        int alpha = 0;
        int pawnScore = Pawn::calculateScore(board,gameStage,alpha);
        int oneBlackDoubledPawn = -(EvalTables::PawnTable[OPENING][Pawn::DOUBLED]*gameStage +
        EvalTables::PawnTable[ENDGAME][Pawn::DOUBLED]*alpha )/Eval::TOTAL_MATERIAL;

        REQUIRE(pawnScore == oneBlackDoubledPawn);
    }

    SECTION("Isolated/Passed Pawns")
    {
        Board board("4k3/p1p4p/p3pP2/7P/2pP2p1/1P6/P4PP1/4K3 b KQkq - 0 1");
        REQUIRE(Pawn::countPawnsInFile(board,2,BLACK) == 2);
        REQUIRE(Pawn::countPawnsInFile(board,5,WHITE) == 2);
        REQUIRE(Pawn::hasNeighbors(board,3,WHITE) == false);
        REQUIRE(Pawn::hasNeighbors(board,5,WHITE) == true);
        REQUIRE(Pawn::hasNeighbors(board,4,BLACK) == false);
        REQUIRE(Pawn::hasNeighbors(board,3,BLACK) == true);
        REQUIRE(Pawn::doubledPawns(board) == -1);
        REQUIRE(Pawn::passedPawns(board) == 1);
        REQUIRE(Pawn::isolatedPawns(board) == -2);
    }

        SECTION("Supported Pawn")
    {
        Board board("rnbqkbnr/pppppppp/8/8/8/3P4/PPP1PPPP/RNBQKBNR w KQkq -");
        REQUIRE(Pawn::supportedPawns(board) == 1);
        board = Board("7k/2p1p3/3p1p2/8/8/3P4/2P1P3/7K w - -");
        REQUIRE(Pawn::supportedPawns(board) == -1);
        board = Board("rnbqkbnr/pp2pppp/2pp4/8/4P3/3P4/PPP2PPP/RNBQKBNR w KQkq -");
        REQUIRE(Pawn::supportedPawns(board) == 0);
    }
}

TEST_CASE("Pawn zobrist keys")
{
	Tables::init();	
	ZK::initZobristKeys();
	
    SECTION("Test Zobrist pawn key on quiet move")
    {
        Board board;
        MoveGen moveGen(board);
        Zkey initialKey = board.pawnsKey;

        auto moves = moveGen.generateMoves();

        for(Move move : moves)
        {
            board.executeMove(move);
    
            REQUIRE(initialKey != board.pawnsKey);           
        
            board.undoMove(move);
            REQUIRE(initialKey == board.pawnsKey);
        }
    }
}
