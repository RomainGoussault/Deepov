/*
 * Utils.cpp
 *
 *  Created on: 24 sept. 2014
 */
#include "Utils.hpp"
#include "Color.hpp"
#include "MoveGen.hpp"
#include "Search.hpp"
#include "MagicMoves.hpp"

#include "math.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <boost/algorithm/string.hpp>


void Utils::getCastling(std::string const& castleString, int &castlingRights)
{
	castlingRights = 0b0000;
	if (castleString[0] == '-')
	{
		return;
	}
	else
	{
		for (unsigned int i=0; i<castleString.size(); ++i)
		{
			if (castleString[i]=='K')
			{
				castlingRights |= 0x1;
			}
			else if (castleString[i]=='Q')
			{
				castlingRights |= 0x2;
			}
			else if (castleString[i]=='k')
			{
				castlingRights |= 0x4;
			}
			else if (castleString[i]=='q')
			{
				castlingRights |= 0x8;
			}
		}
	}
}

//Waiting to have a fix for stoi
int Utils::convertStringToInt(std::string const& fenMoveCounter)
{
	int counter = 0;
	for (unsigned int i=0; fenMoveCounter[i] != '\0';++i)
	{
		counter = counter*10 + (fenMoveCounter[i]- '0') ;
	}
	return counter;
}

void Utils::getPerformanceIndicator()
{
	for(int i = 0; i < 5; i++)
	{
		int n = 0; //TODO implement node count in Search

		std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -"));
		Search s(sp);

		std::chrono::high_resolution_clock::time_point t1 =
				std::chrono::high_resolution_clock::now();

		s.negaMaxRoot(6);

		//Use other position
		sp = std::shared_ptr<Board>(new Board("rnb1k1nq/p7/1p1pp3/3P2N1/P1R5/2P1Q1P1/1p1P3P/5RK1 b q -"));
		s.negaMaxRoot(7);

		std::chrono::high_resolution_clock::time_point t2 =
				std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> time_span = std::chrono::duration_cast<
				std::chrono::duration<double>>(t2 - t1);

		int nodesPerSec = n/time_span.count();
		std::cout << "It took me " << time_span.count() << " seconds.";
		std::cout << "kNodes per sec: " << nodesPerSec / 1000;

		std::cout << std::endl;
	}

}
