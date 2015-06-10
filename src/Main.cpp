//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <memory>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>

#include "Color.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"

int main() {

	Utils::getPerformanceIndicator();
	Utils::getPerformanceIndicator();
	//Romain : 9sec = 995 556 Nodes/sec
	// -O3 1.6sec 5 609 501 Nodes/sec
	// Navid -O3 9sec 100 000 N/sec
	//Stockfish 180 385 601Nodes/sec

    std::string str;
    std::cin >> str;
	return 0;
}
