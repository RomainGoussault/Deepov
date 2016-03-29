#include "MoveOrdering.hpp"

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

