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
#include "Move.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"
#include "Eval.hpp"


TEST_CASE( "Test move rating", "[moveordering]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("8/8/3k4/4b3/2nnn3/2nQn3/2nnn3/7K w - - 0 1"));
	MoveGen moveGen(*sp);

   std::vector<Move> moveList = moveGen.generateMoves();
   
   MoveOrdering moveOrder;
   moveOrder.rateMoves(moveList,sp, 1, false);

   for (auto it=moveList.begin(); it<moveList.end(); it++)
   {
       REQUIRE(it->getMoveRating() == Piece::KNIGHT_VALUE - Piece::QUEEN);
   }
}


TEST_CASE( "Compare sort methods", "[moveordering]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();

	std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("n1b1kbn1/3pppp1/1r6/1q3R2/8/8/4PPPP/4KBN1 w KQkq -"));
	MoveGen moveGen(*sp);

	std::vector<Move> moveList = moveGen.generateMoves();
   
   MoveOrdering moveOrder;
   bool isSEE = false;
   moveOrder.rateMoves(moveList,sp, 1, isSEE);
   moveOrder.sortMoves(moveList);

   Move bestMove=*std::begin(moveList);

   REQUIRE(bestMove.toShortString() == "f5b5");

   //With SEE
   moveOrder.clearKillers();
   isSEE = true;
   moveOrder.rateMoves(moveList,sp, 1, isSEE);
   moveOrder.sortMoves(moveList);

   bestMove=*std::begin(moveList);

   REQUIRE(bestMove.toShortString() != "f5b5");

}
