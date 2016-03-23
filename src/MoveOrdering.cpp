#include "MoveOrdering.hpp"

MoveOrdering::MoveOrdering() {}


void MoveOrdering::rateMoves(std::vector<Move>& moveList)
{

	int i = 0;
	for(Move move : moveList)
	{
		unsigned int score;

		if(move.isPromotion())
		{
			score += Eval::pieceTypeToValue(move.getPromotedPieceType()-Piece::PAWN_VALUE);
		}

		if(move.isCapture())
		{
			score += Eval::pieceTypeToValue(move.getCapturedPieceType());
		}

		move.setMoveRating(score);
		i++;
	}
}


// Get only the max and remove or sort ?
/*Move MoveOrdering::getBestCandidate(std::vector<Move>& moveList)
{
    auto it = std::max_element(std::begin(myMovesRatings), std::end(myMovesRatings)); // Returns an iterator to the max element
    *it = -1;// Set this move to a negative value
    return moveList[it-moveList.begin()];
} */

