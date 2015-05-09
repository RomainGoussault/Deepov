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
#include "FastBoard.hpp"
#include "FastMove.hpp"
#include "MagicMoves.hpp"

int main() {

	initmagicmoves();
	FastBoard fb = FastBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
	std::cout << fb.perft(3) << std::endl;

	return 0;
}
