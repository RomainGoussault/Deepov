
#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
    public:
        Game();
        Game(Player whitePlayer, Player blackPlayer);

        ~Game();


    private:
        Board myBoard;
        Player myWhitePlayer;
        Player myBlackPlayer;

};

#endif // GAME_H
