#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Move.hpp"
#include "Board.hpp"

class Player
{
    public:
        Player();
        Player(Board board);
        Player(Board board, std::string name);

        ~Player();
        std::string getName() { return myName; }
        void setName(std::string val) { myName = val; }
        Board getBoard() { return myBoard; }
        void setBoard(Board val) { myBoard = val; }

    private:
        Board *myBoard;
        std::string myName;
};

#endif // PLAYER_H

