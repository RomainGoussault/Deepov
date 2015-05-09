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


	FastBoard fb = FastBoard("8/8/8/8/8/8/6bn/5qr1 b - -");
//	FastBoard fb = FastBoard("8/8/8/8/8/8/6NN/5QR1 w - -");
	std::cout << fb << std::endl;

	int size = fb.getRookPseudoLegalMoves(BLACK).size();
	std::cout << size << std::endl;

	FastMove move = fb.getRookPseudoLegalMoves(BLACK)[0];
	fb.executeMove(move);
	std::cout << fb << std::endl;

	fb.undoMove(move);
	std::cout << fb << std::endl;


	return 0;
}
