
#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
    public:
        Game(Board &board, Player &whitePlayer, Player &blackPlayer);
        int perft(int depth);

        ~Game();


    private:
        Board* myBoardptr;
        Player* myWhitePlayer;
        Player* myBlackPlayer;

};

#endif // GAME_H
