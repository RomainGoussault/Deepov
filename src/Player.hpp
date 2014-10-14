#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Move.hpp"
#include "Board.hpp"

class Player
{
    public:
        Player();
        Player(Board &board);
        Player(Board &board, std::string name);

        ~Player();

        std::string getName() { return myName; }
        void setName(std::string val) { myName = val; }
        Board getBoard() { return *myBoardptr; }
        Board* getBoardptr() { return myBoardptr; }
        void setBoard(Board val) { *myBoardptr = val; }
        void setBoardptr(Board* val) { myBoardptr = val; }

    private:
        Board* myBoardptr;
        std::string myName;
};

#endif // PLAYER_H

