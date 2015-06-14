/*
 * Utils.cpp
 *
 *  Created on: 24 sept. 2014
 */
#include "Utils.hpp"
#include "Color.hpp"
#include "MoveGen.hpp"
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
	MagicMoves::initmagicmoves();

    Board board("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -");
	MoveGen moveGen(board);

	std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();

	int n = 0; //board.perft(5);
	board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	n += board.perft(5);

	std::chrono::high_resolution_clock::time_point t2 =
			std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> time_span = std::chrono::duration_cast<
			std::chrono::duration<double>>(t2 - t1);

	int nodesPerSec = n/time_span.count();
	std::cout << "It took me " << time_span.count() << " seconds.";
	std::cout << "kNodes per sec: " << nodesPerSec / 1000;

	std::cout << std::endl;
}

unsigned int Utils::countBBBitsSet(U64 v)
{
    v = v - ((v >> 1) & (std::uint64_t)~(std::uint64_t)0/3);                           // temp
    v = (v & (std::uint64_t)~(std::uint64_t)0/15*3) + ((v >> 2) & (std::uint64_t)~(std::uint64_t)0/15*3);      // temp
    v = (v + (v >> 4)) & (std::uint64_t)~(std::uint64_t)0/255*15;                      // temp
    unsigned int c = (std::uint64_t)(v * ((std::uint64_t)~(std::uint64_t)0/255)) >> (sizeof(std::uint64_t) - 1) * CHAR_BIT; // count
    return c;
}

U64 Utils::inBetween(int sq1, int sq2) { //TODO an array look is better https://chessprogramming.wikispaces.com/Square+Attacked+By#Legality%20Test-In%20Between-Rectangular%20Lookup
   const U64 m1   = C64(-1);
   const U64 a2a7 = C64(0x0001010101010100);
   const U64 b2g7 = C64(0x0040201008040200);
   const U64 h1b7 = C64(0x0002040810204080); /* Thanks Dustin, g2b7 did not work for c1-a3 */
   U64 btwn, line, rank, file;

   btwn  = (m1 << sq1) ^ (m1 << sq2);
   file  =   (sq2 & 7) - (sq1   & 7);
   rank  =  ((sq2 | 7) -  sq1) >> 3 ;
   line  =      (   (file  &  7) - 1) & a2a7; /* a2a7 if same file */
   line += 2 * ((   (rank  &  7) - 1) >> 58); /* b1g1 if same rank */
   line += (((rank - file) & 15) - 1) & b2g7; /* b2g7 if same diagonal */
   line += (((rank + file) & 15) - 1) & h1b7; /* h1b7 if same antidiag */
   line *= btwn & -btwn; /* mul acts like shift by smaller square */
   return line & btwn;   /* return the bits on that line in-between */
}
