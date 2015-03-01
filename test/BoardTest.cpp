#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Rook.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "Color.hpp"
#include "Piece.hpp"
#include "King.hpp"
#include "Move.hpp"


TEST_CASE( "is position on Board test", "[board]" )
{
	Board board;
	Position position1(0, 0);
	Position position2(7,7);
	Position position3(6,4);

	Position position4(8,4);
	Position position5(4,8);
	Position position6(-1,4);
	Position position7(6,-1);

	REQUIRE(board.isPositionOnBoard(position1));
	REQUIRE(board.isPositionOnBoard(position2));
	REQUIRE(board.isPositionOnBoard(position3));

	REQUIRE_FALSE(board.isPositionOnBoard(position4));
	REQUIRE_FALSE(board.isPositionOnBoard(position5));
	REQUIRE_FALSE(board.isPositionOnBoard(position6));
	REQUIRE_FALSE(board.isPositionOnBoard(position7));
}

TEST_CASE( "is position free", "[board]" )
{
	Board board;

	Position position1(0, 0);
	Position position2(7,7);
	Position position3(6,4);

	PiecePtr rook1(new Rook(position1, WHITE));
	PiecePtr rook2(new Rook(position2, WHITE));
	PiecePtr rook3(new Rook(position3, WHITE));

	board.addPiece(rook1);
	board.addPiece(rook2);
	board.addPiece(rook3);

	Position position4(5,4);
	Position position5(4,6);
	Position position6(5,7);
	Position position7(4,0);

	REQUIRE_FALSE(board.isPositionFree(position1));
	REQUIRE_FALSE(board.isPositionFree(position2));
	REQUIRE_FALSE(board.isPositionFree(position3));

	REQUIRE(board.isPositionFree(position5));
	REQUIRE(board.isPositionFree(position4));
	REQUIRE(board.isPositionFree(position6));
	REQUIRE(board.isPositionFree(position7));
}

TEST_CASE( "getPieces", "[board]" )
{
	Board board;

	Position position1(0, 0);
	Position position2(7,7);
	Position position3(6,4);

	PiecePtr rook1(new Rook(position1, WHITE));
	PiecePtr rook2(new Rook(position2, BLACK));
	PiecePtr rook3(new Rook(position3, WHITE));

	board.addPiece(rook1);
	board.addPiece(rook2);
	board.addPiece(rook3);

	int numberWhitePieces = board.getPieces(WHITE).size();
	int numberBlackPieces = board.getPieces(BLACK).size();

	REQUIRE(numberWhitePieces == 2);
	REQUIRE(numberBlackPieces == 1);
}

TEST_CASE( "execute Move", "[board]" )
{
	Board board;

	Position position1(0, 0);
	Position position2(0, 1);
	Position position3(1, 0);

	PiecePtr rook1(new Rook(position1, BLACK));
	PiecePtr rook2(new Rook(position2, WHITE));
	PiecePtr rook3(new Rook(position3, BLACK));

	board.addPiece(rook1);
	board.addPiece(rook2);
	board.addPiece(rook3);

	std::vector<Move> rookMoves = rook1->getPseudoLegalMoves(board);
	Move move = rookMoves[0];


	int numberWhitePieces = board.getPieces(WHITE).size();
	int numberBlackPieces = board.getPieces(BLACK).size();

	REQUIRE(numberWhitePieces == 1);
	REQUIRE(numberBlackPieces == 2);

	board.executeMove(move);

	numberWhitePieces = board.getPieces(WHITE).size();
	numberBlackPieces = board.getPieces(BLACK).size();

	REQUIRE(numberWhitePieces == 0);
	REQUIRE(numberBlackPieces == 2);

	board.undoMove(move);

	numberWhitePieces = board.getPieces(WHITE).size();
	numberBlackPieces = board.getPieces(BLACK).size();

	REQUIRE(numberWhitePieces == 1);
	REQUIRE(numberBlackPieces == 2);
}

TEST_CASE( "get Board from FEN", "[board]" )
{
	Board board("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

	int numberWhitePieces = board.getPieces(WHITE).size();
	int numberBlackPieces = board.getPieces(BLACK).size();
	int colorToPlay = board.getColorToPlay();
	bool firstMove = board.isFirstMove();
	int movesNumber = board.getMovesCounter();
	int halfMoveNumber = board.getHalfMovesCounter();
	boost::optional<Position> enPassantTarget = board.getEnPassantPosition();
	bool K,Q,k,q;
	K = board.getCastling(0);
	Q = board.getCastling(1);
	k = board.getCastling(2);
	q = board.getCastling(3);

	REQUIRE(numberWhitePieces == 16);
	REQUIRE(numberBlackPieces == 16);
	REQUIRE(colorToPlay ==  BLACK);
	REQUIRE(firstMove == true);
	REQUIRE(movesNumber == 0);
	REQUIRE(halfMoveNumber == 1);
	REQUIRE(enPassantTarget.get() == Position(4,2));
	REQUIRE(K == true);
	REQUIRE(Q == true);
	REQUIRE(k == true);
	REQUIRE(q == true);
}

TEST_CASE( "attacked positions", "[board]" )
{
	SECTION( "attacked positions with kings only")
	{
		Board board("8/2k5/8/8/8/2K5/8/8 w - - 0 1");

		REQUIRE(board.getAttackedPositions(BLACK).size() == 8);
		REQUIRE(board.getAttackedPositions(WHITE).size() == 8);
	}

	SECTION( "attacked positions with kings and a rook" )
	{
		Board board("8/2k5/8/2R5/8/2K5/8/8 b - - 0 1");

		REQUIRE(board.getAttackedPositions(BLACK).size() == 8);
		REQUIRE(board.getAttackedPositions(WHITE).size() == (8+11));
	}

	SECTION( "isPositionAttacked()" )
	{
		Board board("8/8/1r4K1/N7/8/5k2/1R6/8 w - - 0 1");

		REQUIRE(board.isPositionAttacked(Position(0,0), WHITE) == false);
		REQUIRE(board.isPositionAttacked(Position(5,1), WHITE) == true);
		REQUIRE(board.isPositionAttacked(Position(7,7), WHITE) == false);
		REQUIRE(board.isPositionAttacked(Position(7,7), BLACK) == false);
		REQUIRE(board.isPositionAttacked(Position(2,3), BLACK) == false);
		REQUIRE(board.isPositionAttacked(Position(2,3), WHITE) == true);
	}
}

TEST_CASE( "check", "[board]" )
{
	SECTION( "board is check")
	{
		Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
		REQUIRE(board.isCheck(WHITE) == false);
		REQUIRE(board.isCheck(WHITE) == false);

		board = Board("4k3/8/3r4/8/8/3K4/8/8 w - - 0 1");
		REQUIRE(board.isCheck(WHITE) == true);
		REQUIRE(board.isCheck(BLACK) == false);

		board = Board("8/8/3r4/5N2/3k4/8/3K4/8 b - - 0 1");
		REQUIRE(board.isCheck(WHITE) == false);
		REQUIRE(board.isCheck(BLACK) == true);
	}
}


TEST_CASE( "executeMove for Castling", "[board]" )
{

    SECTION( "executeMove")
	{
        Board board("rnbqk2r/pppppppp/8/8/4P3/8/PPPP1PPP/R1BQK2R b KQkq e3 0 1");

        bool K = board.getCastling(2);
        bool Q = board.getCastling(3);
        Position position(4,7);
        PiecePtr kingPtr= board.getPiecePtr(position);

        REQUIRE(std::dynamic_pointer_cast<King>(kingPtr) != nullptr);

        std::vector<Move> kingMoves = kingPtr->getPseudoLegalMoves(board) ;
        Move theCastling(position,position);

        REQUIRE(kingPtr->getPseudoLegalMoves(board).size() == 2);
        REQUIRE(K == true);
        REQUIRE(Q == true);

        if ((kingMoves[0]).isCastling() == true)
        {
            theCastling = kingMoves[0];
        }
        else
        {
            theCastling = kingMoves[1];
        }

        board.executeMove(theCastling);

        K = board.getCastling(2);
        Q = board.getCastling(3);
        kingMoves = kingPtr->getPseudoLegalMoves(board);

        REQUIRE(kingPtr->getPseudoLegalMoves(board).size() == 1);
        REQUIRE(K == false);
        REQUIRE(Q == false);

        Position kingPostition(6,7);
        Position rookPosition(5,7);
        kingPtr = board.getPiecePtr(kingPostition);
        PiecePtr rookPtr = board.getPiecePtr(rookPosition);

        REQUIRE(std::dynamic_pointer_cast<King>(kingPtr) != nullptr);
        REQUIRE(std::dynamic_pointer_cast<Rook>(rookPtr) != nullptr);
	}

    SECTION( "undoMove")
	{


	}

}

TEST_CASE( "executeMove for Promotion", "[board]" )
{
    SECTION("Promotion without capture")
    {
        Board board("8/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        /* Select the pawn */
        Position position(2,6);
        PiecePtr pawn(board.getPiecePtr(position));
        Position destination(2,7);

        /* Set the Move */
        Move promotionMove = Move(position,destination);
        PiecePtr promotedPtr(new Queen(destination, board.getColorToPlay()));
        REQUIRE(std::dynamic_pointer_cast<Queen>(promotedPtr) != nullptr);
        promotionMove.setPromotedPiece(promotedPtr);

        /* execute and test */
        board.executeMove(promotionMove);
        REQUIRE(board.getColorToPlay()==BLACK);

        PiecePtr newPiece = board.getPiecePtr(destination);
        REQUIRE(std::dynamic_pointer_cast<Queen>(newPiece) != nullptr);

    }

    SECTION("Promotion with capture")
    {
        Board board("1r6/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        /* Select the pawn */
        Position position(2,6);
        PiecePtr pawn(board.getPiecePtr(position));
        /* Select the rook */
        Position destination(1,7);
        PiecePtr rookPtr = board.getPiecePtr(destination);

        /* Set the Move */
        Move promotionMove = Move(position,destination);
        promotionMove.setCapturedPiece(rookPtr);
        PiecePtr promotedPtr(new Bishop(destination, board.getColorToPlay()));
        REQUIRE(std::dynamic_pointer_cast<Bishop>(promotedPtr) != nullptr);
        promotionMove.setPromotedPiece(promotedPtr);

        /* execute and test */
        board.executeMove(promotionMove);
        REQUIRE(board.getColorToPlay()==BLACK);

        PiecePtr newPiece = board.getPiecePtr(destination);
        REQUIRE(std::dynamic_pointer_cast<Bishop>(newPiece) != nullptr);

        std::vector<PiecePtr> blackPieces = board.getEnemyPieces(WHITE);
        REQUIRE(blackPieces.size() == 1);

    }
}

