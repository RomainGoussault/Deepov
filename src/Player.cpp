 /*  Created on: 13 oct.
 *      Author: Romain & Navid
 */
#include "Player.hpp"

Player::Player() : myBoard(Board board), myName("Player")
{
}

Player::Player(Board board) : myBoard(board), myName("Player")
{
}

Player::Player(Board board, std::string name) : myBoard(board), myName(name)
{
}

