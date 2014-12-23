/*
 * Knight.hpp
 *
 */

#include "Knight.hpp"


Knight::Knight(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Knight::getPseudoLegalMoves(const Board &board)
{
    std::vector<Move> knightMoves;
    PiecePtr otherPiece;
	std::array<Position,8> destinations;

	destinations[0] = myPosition.deltaXY(1,2);
	destinations[1] = myPosition.deltaXY(1,-2);
	destinations[2] = myPosition.deltaXY(-1,2);
	destinations[3] = myPosition.deltaXY(-1,-2);
	destinations[4] = myPosition.deltaXY(2,1);
	destinations[5] = myPosition.deltaXY(2,-1);
	destinations[6] = myPosition.deltaXY(-2,1);
	destinations[7] = myPosition.deltaXY(-2,1);

	for(const auto& destination : destinations)
	{
		if (board.isPositionOnBoard(destination))
		{
			Move possibleMove = Move(myPosition, destination);
			if (board.isPositionFree(destination))
			{
				knightMoves.push_back(possibleMove);
			}
			else
			{
				otherPiece = board.getPiecePtr(destination);
				// look for capture
				if (areColorDifferent(*otherPiece))
				{
					possibleMove.setCapturedPiece(otherPiece);
					knightMoves.push_back(possibleMove);
				}
			}
		}
	}

    return knightMoves;
}

std::vector<Position> Knight::getAttackedPositions(const Board &board)
{
	std::vector<Position> attackedPositions;
	std::array<Position,8> destinations;

	destinations[0] = myPosition.deltaXY(1,2);
	destinations[1] = myPosition.deltaXY(1,-2);
	destinations[2] = myPosition.deltaXY(-1,2);
	destinations[3] = myPosition.deltaXY(-1,-2);
	destinations[4] = myPosition.deltaXY(2,1);
	destinations[5] = myPosition.deltaXY(2,-1);
	destinations[6] = myPosition.deltaXY(-2,1);
	destinations[7] = myPosition.deltaXY(-2,1);

	for(const auto& destination : destinations)
	{
		if (board.isPositionOnBoard(destination))
		{
			attackedPositions.push_back(destination);
		}
	}

	return attackedPositions;
}
