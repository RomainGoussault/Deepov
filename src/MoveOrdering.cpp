#include "MoveOrdering.hpp"



void MoveOrdering::setNewKiller(const Move& move,const unsigned int ply)
{
    /* For now we save the two killer moves in the historic order as in Crafty.
    TODO : affect a score to each killer */

    if (!move.isPromotion() && move.isCapture()) 
    {

        /* Fill ply with no killer with null moves (vector) */ 
        while (myKiller1.size() < ply)
        {
            myKiller1.push_back(Move());
        }
        while (myKiller2.size() < ply)
        {
            myKiller2.push_back(Move());
        }

        myKiller2[ply] = myKiller1[ply];
        myKiller1[ply] = move;

    } 
    
}

void MoveOrdering::rateMoves(std::vector<Move>& moveList)
{
	for(Move& move : moveList)
	{
		unsigned int score=0;

		if(move.isPromotion())
		{
			score += Eval::pieceTypeToValue(move.getPromotedPieceType())-Piece::PAWN_VALUE;
		}

		if(move.isCapture())
		{
			score += Eval::pieceTypeToValue(move.getCapturedPieceType());
		}

		move.setMoveRating(score);
	}
}

void MoveOrdering::rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board)
{
	for(Move& move : moveList)
	{
		unsigned int score=0;

		if(move.isPromotion())
		{
			score += Eval::pieceTypeToValue(move.getPromotedPieceType())-Piece::PAWN_VALUE;
		}

		if(move.isCapture())
		{
			score += board->seeCapture(move, Utils::getOppositeColor(board->getColorToPlay()));
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

