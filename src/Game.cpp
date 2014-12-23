 /*  Created on: 13 oct.
 *      Author: Romain & Navid
 */

#include "Game.hpp"

Game::Game(Board &board, Player &whitePlayer, Player &blackPlayer) : myBoardptr(&board), myWhitePlayer(&whitePlayer), myBlackPlayer(&blackPlayer)
{
    if (whitePlayer.getBoardptr() != myBoardptr)
    {
        whitePlayer.setBoardptr(myBoardptr);
    }

    if (blackPlayer.getBoardptr() != myBoardptr)
    {
        blackPlayer.setBoardptr(myBoardptr);
    }
}

int Game::perft(int depth)
{
	int nMoves, i;
	int nodes = 0;

	if (depth == 0)
	{
		return 1;
	}

	std::vector<Move> moves = myBoardptr->getLegalMoves();
	nMoves = moves.size();

	for (i = 0; i < nMoves; i++)
	{
		Move move = moves[i];
		myBoardptr->executeMove(move);
		nodes += perft(depth - 1);
		myBoardptr->undoMove(move);
	}

	return nodes;
}
