// Ca va groooos ?
//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Position.hpp"
#include "Rook.hpp"
#include "Color.hpp"
#include "Board.hpp"
using namespace std;

int main()
{
	cout << "!!!Hello World !!!" << endl;
	Position position(3, 4);
	Position deltaPosition = position.deltaX(10);
	Rook rook(position, Color::WHITE);

	cout << position.print() << endl;
	cout << deltaPosition.print() << endl;

	Board board;
	board.addPiece(rook);

	return 0;
}
