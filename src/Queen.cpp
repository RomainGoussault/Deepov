/*
 * Queen.cpp
 *
 */

#include "Queen.hpp"
#include "Bishop.hpp"
#include "Rook.hpp"
#include "Board.hpp"

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
