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
#include "MagicMoves.hpp"

int main() {

	initmagicmoves();

	FastBoard fb = FastBoard("1bq1b2p/p2p1pp1/2Bk4/1N6/4r1Q1/B6P/PP1PPPP1/3K2R1 b K -");
	std::cout << fb << std::endl;

	int size = fb.getRookPseudoLegalMoves(WHITE).size();
	std::cout << size << std::endl;

	return 0;
}
