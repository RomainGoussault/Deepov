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


int main()
{
	Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	std::cout << board << std::endl;

	return 0;
}
