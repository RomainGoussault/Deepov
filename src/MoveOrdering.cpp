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
    auto ttEntry = globalTT.probeTT(board->key, 0); // returns non nullpr if key exists and depth is greater
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

