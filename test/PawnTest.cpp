#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"


TEST_CASE( "Pawn possible moves", "[pawn]" )
{

    SECTION("Pawn on starting rank")
    {
        Board board("4k3/8/8/8/8/8/4P3/4K3 w - - 0 1");
        Position position(4,1);
        PiecePtr pawnPtr = board.getPiecePtr(position);
        int size = pawnPtr->getPseudoLegalMoves(board).size();
        REQUIRE(size == 2);
    }

    SECTION("Pawn starting game")
    {
        Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        Position position(1,0);
        PiecePtr pawn = board.getPiecePtr(position);
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 2);
    }

    SECTION("Pawn blocked by enemy pieces")
    {
        Board board("rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq - 0 1");
        Position position(3,3);
        PiecePtr pawn = board.getPiecePtr(position);
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 0);
    }

    SECTION("Pawn with possible capture")
    {
        Board board("rnbqkbnr/ppp2ppp/8/3pp3/3PP3/8/PPP2PPP/RNBQKBNR w KQkq - 0 1");
        Position position(3,3);
        PiecePtr pawn = board.getPiecePtr(position);
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 1);
    }

    SECTION("Promotion")
    {
        Board board("8/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        Position position(2,6);
        PiecePtr pawn(board.getPiecePtr(position));
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 4);
    }
    SECTION("Promotion with capture")
    {
        Board board("1r6/2P1k3/8/3K4/8/8/8/8 w - - 0 1");
        Position position(2,6);
        PiecePtr pawn(board.getPiecePtr(position));
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 8);
    }

    /* Tests with EnPassant */

    SECTION("EnPassant from FEN")
    {
        Board board("rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
        Position position(3,3);
        PiecePtr pawn(board.getPiecePtr(position));
        int size = pawn->getPseudoLegalMoves(board).size();
        REQUIRE(size == 2);
    }
    /* TODO tests execute/undo enPassant/Promotion/Starting rank */

}
