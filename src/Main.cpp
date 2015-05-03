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

int main() {
	FastBoard fb = FastBoard("8/1b2kB2/7b/8/8/2qK4/8/8 w - -");

	std::cout << FastBoard::printBitBoard(fb.getBlackBishops()) << std::endl;
	std::cout << fb << std::endl;

	std::vector<FastMove> v = fb.getKingPseudoLegalMoves(WHITE) ;

	for(std::vector<FastMove>::iterator it = v.begin(); it != v.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}
