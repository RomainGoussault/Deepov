/*
 * Queen.cpp
 *
 */

#include "Queen.hpp"

Queen::Queen(Position position, int color) : Piece(position, color)
{
}

std::vector<Move> Queen::getPseudoLegalMoves(Board &board)
{
	std::vector<Move> rookMoves = Rook::getRookMoves(board, shared_from_this());
	std::vector<Move> bishopMoves = Bishop::getBishopMoves(board, shared_from_this());

	//Append the bishop moves to the rookMoves
	rookMoves.insert(rookMoves.end(), bishopMoves.begin(), bishopMoves.end());
	return rookMoves;
}

std::vector<Position> Queen::getAttackedPositions(Board &board)
{
	std::vector<Position> rookAttackedPositions = Rook::getAttackedPositions(board, shared_from_this());
	std::vector<Position> bishopAttackedPositions = Bishop::getAttackedPositions(board, shared_from_this());

	//Append the bishop attackedPositions to the rook attackedPositions
	rookAttackedPositions.insert(rookAttackedPositions.end(), bishopAttackedPositions.begin(), bishopAttackedPositions.end());

	return rookAttackedPositions;
}
