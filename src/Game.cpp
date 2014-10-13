 /*  Created on: 13 oct.
 *      Author: Romain & Navid
 */

#include "Game.hpp"

Game::Game()
{
    Board myBoard;
    Player myWhitePlayer(myBoard,"Player 1");
    Player myBlackPlayer(myBoard,"Player 2");

}

Game::Game(Player whitePlayer, Player blackPlayer) : myWhitePlayer(whitePlayer), myBlackPlayer(blackPlayer)
{
    Board myBoard;
    if (whitePlayer.getBoard() != myBoard)
    {
        whitePlayer.setBoard(myBoard);
    }

    if (blackPlayer.getBoard() != myBoard)
    {
        blackPlayer.setBoard(myBoard);
    }
}
