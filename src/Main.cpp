// Ca va groooos ?
//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "Color.hpp"
#include "Position.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Rook.hpp"

using namespace std;

int main()
{
    Position position(0, 0);
    Position position2(0, 1);
    Position position3(0, 2);
    Board board;

    Rook rook(position, BLACK);
    Rook rook2(position2, BLACK);


	PiecePtr rook3(new Rook(position3, BLACK));
    board.addPiece(rook3);

	//PiecePtr p = board.getPiecePtr(position);
   // cout << p->getChar() << endl; //should be 'r'..
    cout << board << endl;
/*
    std::vector<Move> rookMoves = rook.getPseudoLegalMoves(board); // should be 14
    cout << "number of pseudo legal moves should be 7: " << rookMoves.size() << endl;

    for( std::vector<Move>::const_iterator i = rookMoves.begin(); i != rookMoves.end(); ++i)
    {
        cout << *i << endl;
    }*/
 
   return 0;
}
