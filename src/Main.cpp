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

	FastBoard fb = FastBoard("8/8/8/8/8/8/2Q5/N7 w - -");
	std::cout << fb << std::endl;

	int size = fb.getKnightPseudoLegalMoves(WHITE).size();
	std::cout << size << std::endl;

	FastMove move = fb.getKnightPseudoLegalMoves(WHITE)[0];
	fb.executeMove(move);
	std::cout << fb << std::endl;


	return 0;
}
