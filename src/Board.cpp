/*
 * Board.cpp
 *
 *  Created on: 24 sept. 2014
 *      Author: Romain
 */
#include <iostream>

#include "Board.hpp"

Board::Board()
{
}

void Board::addPiece(Piece piece, Position position)
{
	myPieces[position.getX()][position.getY()] = piece;
}

void Board::addPiece(Piece piece)
{
	addPiece(piece, piece.getPosition());
}

bool Board::isPositionFree(Position position)
{
	return getPiece(position).isEmpty();
}

bool Board::isPositionOnBoard(Position position)
{
	char x = position.getX();
	char y = position.getY();

	if (x > BOARD_SIZE || y > BOARD_SIZE)
	{
		return false;
	}

	if (x < 0 || y < 0)
	{
		return false;
	}

	return true;
}

Piece Board::getPiece(Position position)
{
	return myPieces[position.getX()][position.getY()];
}

std::vector<Move> Board::getPseudoLegalMoves(Piece piece)
{
	switch (piece.getValue())
	{
	case Piece::ROOK:
		return getRookMoves(piece);
		break;

	default:
		std::cout << "Error: Unknown Piece" << std::endl;
		std::vector<Move> emptyVector;
		return emptyVector;
	}
}

std::vector<Move> Board::getRookMoves(Piece piece)
{
	std::vector<Move> rookMoves;
	//TODO Implement

	Position origin(0, 0);
	Position destination(0, 0);
	Move move(origin, destination);

	rookMoves.push_back(move);

	return rookMoves;
}
