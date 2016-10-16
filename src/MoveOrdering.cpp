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

#include "MoveOrdering.hpp"
#include <algorithm>
#include "TT.hpp"

void MoveOrdering::clearKillers()
{
    for (unsigned int i=0 ; i<64 ; i++)
    {
        myKiller1[i] = Move();
        myKiller2[i] = Move();
    } 
}

void MoveOrdering::setNewKiller(const Move& move, const unsigned int ply)
{
    /* For now we save the two killer moves in the historic order as in Crafty.
    TODO : affect a score to each killer */

    if (!move.isPromotion() && !move.isCapture()) 
    {
        myKiller2[ply] = myKiller1[ply];
        myKiller1[ply] = move;
    } 
}

void MoveOrdering::rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board, const unsigned int ply, const bool isSEE)
{
    TTEntry* ttEntry = globalTT.probeTT(board->key, 0); // returns non nullpr if key exists and depth is greater
    Move hashMove = Move();

    if(ttEntry)
    {
        hashMove = ttEntry->getBestmove();

    }

	for(Move& move : moveList)
	{
		unsigned int score=0;

        if(move==hashMove)
        {
           score += 100000;
        } 


		if(move.isPromotion())
		{
			score += Eval::pieceTypeToValue(move.getPromotedPieceType())-Piece::PAWN_VALUE;
		}

		if(move.isCapture())
		{
            if(isSEE)
            {
                score += board->seeCapture(move, Utils::getOppositeColor(board->getColorToPlay()));
            }
            else
            {
                // MVV/LVA
                score += Eval::pieceTypeToValue(move.getCapturedPieceType())-move.getPieceType();
            }
		}

        if (move == myKiller1[ply])
        {
            score += KILLER1_BONUS;
        }

        if (move == myKiller2[ply])
        {
            score += KILLER2_BONUS;
        }

		move.setMoveRating(score);
	}
}

// TODO : find a way to sort only a few first moves
void MoveOrdering::sortMoves(std::vector<Move>& moveList)
{
    std::sort(moveList.rbegin(), moveList.rend());
}

// Get only the max and remove or sort ?
std::vector<Move>::iterator MoveOrdering::getBestCandidate(std::vector<Move>& moveList)
{
    auto it = std::max_element(std::begin(moveList), std::end(moveList)); // Returns an iterator to the max element
    it->setMoveRating(-1);// Set this move to a negative value
    return it;
} 

