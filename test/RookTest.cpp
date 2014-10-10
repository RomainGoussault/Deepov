#include "catch.hpp"
#include "Board.hpp"
#include "Position.hpp"
#include "Rook.hpp"
#include "Piece.hpp"

TEST_CASE( "Rook possible moves ", "[rook]" )
{
    for(int i = 0; i < 8; ++i )
    {
        for(int j = 0; j < 8; ++j )
        {
            Position position(i, j);
            Rook rook(position, BLACK);
            Board board;
            board.addPiece(rook);
            int size = rook.getPseudoLegalMoves(board).size();
            REQUIRE(size == 914);
        }
    }
}
