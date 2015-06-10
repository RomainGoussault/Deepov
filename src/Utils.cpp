/*
 * Utils.cpp
 *
 *  Created on: 24 sept. 2014
 */
#include "Utils.hpp"
#include "Color.hpp"
#include "MoveGen.hpp"
#include "Board.hpp"
#include "MagicMoves.hpp"

#include "math.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <boost/algorithm/string.hpp>

void Utils::getCastling(std::string const& castleString, bool (&castleBool)[4])
{
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
				castleBool[0]=true;
			}
			else if (castleString[i]=='Q')
			{
				castleBool[1]=true;
			}
			else if (castleString[i]=='k')
			{
				castleBool[2]=true;
			}
			else if (castleString[i]=='q')
			{
				castleBool[3]=true;
			}
			else
			{
				throw std::runtime_error("");
			}
		}
	}
}

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
			else
			{
				throw std::runtime_error("");
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
	initmagicmoves();

    Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	MoveGen moveGen(board);

	std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();

	int n = board.perft(4);
	board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	n += board.perft(5);

	std::chrono::high_resolution_clock::time_point t2 =
			std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<
			std::chrono::duration<double>>(t2 - t1);

	int nodesPerSec = n/time_span.count();
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << "Nodes per sec: " << nodesPerSec;

	std::cout << std::endl;
}
