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
#include "Color.hpp"
#include "Board.hpp"
#include "Rook.hpp"
using namespace std;

int main()
{
	cout << "!!!Hello World !!!" << endl;
	Position position(3, 4);
	Position deltaPosition = position.deltaX(10);
	Rook rook(position, Color::WHITE);

	cout << position.print() << endl;
	cout << deltaPosition.print() << endl;
	cout << rook << endl;
	Board board;
	board.addPiece(rook);
	cout << board.isPositionFree(rook.getPosition())<< endl;
	cout << board.isPositionFree(rook.getPosition().deltaX(1)) << endl;



	board.getPseudoLegalMoves(rook);
	//test travis

	return 0;
}
