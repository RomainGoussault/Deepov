/*
 * Bishop.hpp
 *
 *  Created on: 4 oct. 2014
 *      Author: Romain & Navid
 */

#include "Bishop.hpp"

Bishop::Bishop(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Bishop::getBishopMoves(const Board &board, PiecePtr piecePtr)
{
	std::vector<Move> bishopMoves;
	PiecePtr otherPiece;
	Position myPosition = piecePtr->getPosition();

	// Direction +x +y
	int i = 1;
	Position destination = myPosition.deltaX(i);
	destination = destination.deltaY(i);
	while (board.isPositionOnBoard(destination))
	{
		Move possibleMove(myPosition, destination);

		if (board.isPositionFree(destination))
		{
			bishopMoves.push_back(possibleMove);
		}
		else
		{
			otherPiece = board.getPiecePtr(destination);
			// look for capture
			if (piecePtr->areColorDifferent(*otherPiece))
			{
				possibleMove.setCapturedPiece(otherPiece);
				bishopMoves.push_back(possibleMove);
			}
			break;
		}

		++i;
		destination = myPosition.deltaXY(i,i);
	}

	//Direction +x-y
	i = 1;
	destination = myPosition.deltaX(i);
	destination = destination.deltaY(-i);
	while (board.isPositionOnBoard(destination))
	{
		Move possibleMove(myPosition, destination);

		if (board.isPositionFree(destination))
		{
			bishopMoves.push_back(possibleMove);
		}
		else
		{
			otherPiece = board.getPiecePtr(destination);
			// look for capture
			if (piecePtr->areColorDifferent(*otherPiece))
			{
				possibleMove.setCapturedPiece(otherPiece);
				bishopMoves.push_back(possibleMove);
			}
			break;
		}

		++i;
		destination = myPosition.deltaXY(i,-i);
	}

	//Direction -x+y
	i = 1;
	destination = myPosition.deltaX(-i);
	destination = destination.deltaY(i);
	while (board.isPositionOnBoard(destination))
	{
		Move possibleMove(myPosition, destination);

		if (board.isPositionFree(destination))
		{
			bishopMoves.push_back(possibleMove);
		}
		else
		{
			otherPiece = board.getPiecePtr(destination);
			// look for capture
			if (piecePtr->areColorDifferent(*otherPiece))
			{
				possibleMove.setCapturedPiece(otherPiece);
				bishopMoves.push_back(possibleMove);
			}
			break;
		}

		++i;
		destination = myPosition.deltaXY(-i,i);
	}

	//Direction -x-y
	i = 1;
	destination = myPosition.deltaX(-i);
	destination = destination.deltaY(-i);
	while (board.isPositionOnBoard(destination))
	{
		Move possibleMove(myPosition, destination);

		if (board.isPositionFree(destination))
		{
			bishopMoves.push_back(possibleMove);
		}
		else
		{
			otherPiece = board.getPiecePtr(destination);
			// look for capture
			if (piecePtr->areColorDifferent(*otherPiece))
			{
				possibleMove.setCapturedPiece(otherPiece);
				bishopMoves.push_back(possibleMove);
			}
			break;
		}

		++i;
		destination = myPosition.deltaXY(-i,-i);
	}

	return bishopMoves;
}

std::vector<Position> Bishop::getAttackedPositions(const Board &board, PiecePtr piecePtr)
{
	std::vector<Position> attackedPositions;
	PiecePtr otherPiece;
	Position myPosition = piecePtr->getPosition();

	// Direction +x +y
	int i = 1;
	Position destination = myPosition.deltaXY(i,i);
	while (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);

		if (!board.isPositionFree(destination))
		{
			break;
		}

		++i;
		destination = myPosition.deltaXY(i,i);
	}

	//Direction +x -y
	i = 1;
	destination = myPosition.deltaXY(i,-i);
	while (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);

		if (!board.isPositionFree(destination))
		{
			break;
		}

		++i;
		destination = myPosition.deltaXY(i,-i);
	}

	//Direction -x +y
	i = 1;
	destination = myPosition.deltaXY(-i,i);
	while (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);

		if (!board.isPositionFree(destination))
		{
			break;
		}

		++i;
		destination = myPosition.deltaXY(-i,i);
	}

	//Direction -x -y
	i = 1;
	destination = myPosition.deltaXY(-i,-i);
	while (board.isPositionOnBoard(destination))
	{
		attackedPositions.push_back(destination);

		if (!board.isPositionFree(destination))
		{
			break;
		}

		++i;
		destination = myPosition.deltaXY(-i,-i);
	}

	return attackedPositions;
}

std::vector<Move> Bishop::getPseudoLegalMoves(const Board &board)
{
	return Bishop::getBishopMoves(board, shared_from_this());
}

std::vector<Position> Bishop::getAttackedPositions(const Board &board)
{
    return Bishop::getAttackedPositions(board, shared_from_this());
}
