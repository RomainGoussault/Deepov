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

Piece Board::getPiece(Position position)
{
	return myPieces[position.getX()][position.getY()];
}

std::vector<Move> Board::getPseudoLegalMoves(Piece piece)
{
	switch(piece.getValue())
	    {
	        case Piece::ROOK :
	            return getRookMoves(piece);
	            break;

	        default :
	            std::cout << "Error: Unknown Piece" << std::endl;
	            std::vector<Move> emptyVector;
	            return emptyVector;
	    }
}

std::vector<Move> Board::getRookMoves(Piece piece)
{
    std::vector<Move> rookMoves;
    //TODO Implement

    return rookMoves;
}

