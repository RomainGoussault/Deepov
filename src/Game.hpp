
#ifndef GAME_H
#define GAME_H
#include <string>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
    public:
		Game(Board board);
		//Game(Board &board, Player &whitePlayer, Player &blackPlayer);
        int perft(int depth);

    private:
        Board myBoard;
       // Player* myWhitePlayer;
      //  Player* myBlackPlayer;

};

#endif // GAME_H
