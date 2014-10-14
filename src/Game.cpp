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
