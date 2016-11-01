/*
	Deepov, a UCI chess playing engine.

	Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Utils.hpp"
#include "MoveGen.hpp"
#include "Search.hpp"
#include "MagicMoves.hpp"

#include "math.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
//#include <boost/algorithm/string.hpp>


void Utils::getCastling(std::string const& castleString, unsigned int &castlingRights)
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
unsigned int Utils::convertStringToInt(std::string const& fenMoveCounter)
{
	unsigned int counter = 0;
	for (unsigned int i=0; fenMoveCounter[i] != '\0';++i)
	{
		counter = counter*10 + (fenMoveCounter[i]- '0') ;
	}
	return counter;
}

void Utils::getPerformanceIndicator()
{
	for(unsigned int i = 0; i < 5; i++)
	{
		unsigned int n = 0; //TODO implement node count in Search

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

		unsigned int nodesPerSec = n/time_span.count();
		std::cout << "It took me " << time_span.count() << " seconds.";
		std::cout << "kNodes per sec: " << nodesPerSec / 1000;

		std::cout << std::endl;
	}
}

std::string Utils::Move16ToShortString(const Move16 shortMove)
{
//		The move format is in long algebraic notation.
		std::array<std::string,8> letters = {{"a", "b", "c", "d", "e", "f", "g", "h"}};

        Square origin = static_cast<Square>((shortMove >> 6) & 0x3f);
		unsigned int xOrigin = origin % 8;
		unsigned int yOrigin = (origin / 8)+1;

        Square destination = static_cast<Square>(shortMove & 0x3f);
		unsigned int xDestination = destination % 8;
		unsigned int yDestination = (destination / 8)+1;

		std::string promotionLetter = "";
		unsigned int flag = (shortMove >> 12) & 0x0f;
		if(flag & Move::PROMOTION_FLAG)
		{
			unsigned int promotedType = flag - Move::PROMOTION_FLAG +1;

			if(flag & Move::CAPTURE_FLAG)
			{
				promotedType -= Move::CAPTURE_FLAG;
			}

			if(promotedType == Piece::KNIGHT)
			{
				promotionLetter = "n";
			}
			else if(promotedType == Piece::BISHOP)
			{
				promotionLetter = "b";
			}
			else if(promotedType == Piece::ROOK)
			{
				promotionLetter = "r";
			}
			else if(promotedType == Piece::QUEEN)
			{
				promotionLetter = "q";
			}
		}

		std::stringstream ss;
		ss << letters[xOrigin] << yOrigin << letters[xDestination] << yDestination << promotionLetter;

		return ss.str();
}