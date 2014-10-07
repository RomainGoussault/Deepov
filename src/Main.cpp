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
#include "Position.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "Rook.hpp"
#include <boost/array.hpp>


using namespace std;

int main()
{
    boost::array<int, 4> arr = {{1,2,3,4}};

    Position position(6, 4);
    Rook rook(position, BLACK);
    cout << rook << endl;

    Board board;
    board.addPiece(rook);

    std::vector<Move> rookMoves = rook.getPseudoLegalMoves(board); // should be 14
    cout << "number of pseudo legal moves should be 14: " << rookMoves.size() << endl;


        for( std::vector<Move>::const_iterator i = rookMoves.begin(); i != rookMoves.end(); ++i)
        {
            cout << *i << endl;

        }


    cout << "number of pseudo legal moves should be 14: " << rookMoves.size() << endl;

    return 0;
}
