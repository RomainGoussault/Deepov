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

#include "Types.hpp"
#include "Eval.hpp"
#include "Search.hpp"
#include "Board.hpp"
#include "MoveGen.hpp"
#include "Move.hpp"
#include "MagicMoves.hpp"
#include "Utils.hpp"
#include "Uci.hpp"

//#define PERFORMANCE_TEST



int main() {

	MagicMoves::initmagicmoves();
	Tables::init();

	#ifdef PERFORMANCE_TEST

		Utils::getPerformanceIndicator();

	#else

		Uci uci;
		uci.loop();

	#endif

	return 0;
}
