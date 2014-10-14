 /*  Created on: 13 oct.
 *      Author: Romain & Navid
 */
#include "Player.hpp"

Player::Player() : myBoardptr(NULL), myName("Player")
{
}

Player::Player(Board &board) : myBoardptr(&board), myName("Player")
{
}

Player::Player(Board &board, std::string name) : myBoardptr(&board), myName(name)
{
}

