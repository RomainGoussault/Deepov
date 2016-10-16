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

#include "BitBoardUtils.hpp"


void BitBoardUtils::printBitBoard(const U64 &bitBoard)
{
	std::ostringstream strm;
	for(int rank = 7; rank >= 0 ; rank--)
	{
		strm << rank << "|  ";

		for(unsigned int file = 0; file < 8 ; file++)
		{
			char c = BitBoardUtils::isBitSet(bitBoard, file, rank) ? 'X' : '*';
			strm << c << " ";
		}

		strm << std::endl;
	}

	strm << "   ________________" << std::endl;
	strm << "    0 1 2 3 4 5 6 7" << std::endl;

	std::cout << strm.str() << std::endl;
}
