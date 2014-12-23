 /*  Created on: 13 oct.
 *      Author: Romain & Navid
 */

#include "Game.hpp"

Game::Game(Board board) : myBoard(board)
{
}
/*
Game::Game(Board &board, Player &whitePlayer, Player &blackPlayer) : myBoard(&board), myWhitePlayer(&whitePlayer), myBlackPlayer(&blackPlayer)
{
    if (whitePlayer.getBoardptr() != myBoard)
    {
        whitePlayer.setBoardptr(myBoard);
    }

    if (blackPlayer.getBoardptr() != myBoard)
    {
        blackPlayer.setBoardptr(myBoard);
    }
}
*/
int Game::perft(int depth)
{
	int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

	std::vector<Move> moves = myBoard.getLegalMoves();

	for (const auto move : moves)
	{
		myBoard.executeMove(move);
		nodes += perft(depth - 1);
		myBoard.undoMove(move);
	}

	return nodes;
}
