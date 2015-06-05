#include "catch.hpp"
#include "FastBoard.hpp"
#include "MagicMoves.hpp"
#include "MoveGen.hpp"


TEST_CASE( "Bitboard Pawn EP moves", "[pawn]" )
{
    initmagicmoves();

    SECTION("EnPassant from FEN")
    {
		FastBoard board("rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
		MoveGen moveGen(board);
		REQUIRE((board.getMovesHistory()).size() == 1); // A move is added if there is an EP square

		std::vector<FastMove> epMoves = moveGen.getBlackEnPassantMoves();
		int epSize = epMoves.size();
		REQUIRE(epSize == 1);
    }

    SECTION("EnPassant after execute/undo move")
	{
    	std::shared_ptr<FastBoard> boardPtr = std::make_shared<FastBoard>("rnbqkbnr/1ppppppp/p7/4P3/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2");
        MoveGen moveGen(boardPtr);
		int origin = 53; // F7
		int destination = 37; // F5

		FastMove move(origin, destination, FastMove::DOUBLE_PAWN_PUSH_FLAG, FastMove::PAWN_TYPE);
		boardPtr->executeMove(move);
		REQUIRE((boardPtr->getMovesHistory()).size() == 1);

		boost::optional<FastMove> lastMove(boardPtr->getEnemyLastMove());
		REQUIRE(lastMove);

		REQUIRE((boardPtr->getMovesHistory()).size() == 1);

		std::vector<FastMove> epMoves = moveGen.getWhiteEnPassantMoves();
        int epSize = epMoves.size();
		REQUIRE(epSize == 1);

		boardPtr->executeMove(epMoves[0]);

        boardPtr->undoMove(epMoves[0]);

        //TODO: Test something maybe?
	}
}

TEST_CASE( "Castling" )
{
	SECTION("Castling possible")
	{
		FastBoard board("r3k2r/pppppppp/8/2nqn3/1NBQ1N2/8/PPPPPPPP/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == true);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == true);
	}

	SECTION("Castling not possible because pieces are in the middle")
	{
		FastBoard board("r2nkq1r/pppppppp/8/2B5/3Q4/8/PPPPPPPP/RN2K1NR w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == false);
	}

	SECTION("Castling not possible because pieces attacking")
	{
		FastBoard board("r3k2r/pp1ppppp/4nqN1/N7/1P1Q1N2/b3rP1P/P1RP1PP1/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == false);
	}

	SECTION("Random castling test")
	{
		FastBoard board("r3k2r/Q3ppp1/4n3/Nppp2pR/1RP3P1/b3q1rP/P3N3/R3K2R w KQkq -");
	    MoveGen moveGen(board);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isQueenSideCastlingPossible(BLACK) == true);
	    REQUIRE(moveGen.isKingSideCastlingPossible(WHITE) == false);
	    REQUIRE(moveGen.isKingSideCastlingPossible(BLACK) == true);
	}
}
