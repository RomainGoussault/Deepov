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
	FastBoard fb = FastBoard("r1bq1b2/pp2p1pp/3Bk3/2N5/3r3Q/1B6/PPPrPPPP/R3K2R w KQkq -");
	std::cout << fb << std::endl;

	initmagicmoves();

	int square = 27;
	U64 occupancy = fb.getAllPieces();
	U64 test = Rmagic(square, occupancy) & ~fb.getBlackPieces();
	std::cout << FastBoard::printBitBoard(test) << std::endl;

	return 0;
}
