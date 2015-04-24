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
#include "FastBoard.hpp"

int main() {
	FastBoard fb = FastBoard();
	std::cout << fb << std::endl;

	return 0;
}
