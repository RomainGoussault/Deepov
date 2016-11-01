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

#include "Move.hpp"
#include <iostream>
#include <sstream>

std::string Move::toShortString() const
{
//		The move format is in long algebraic notation.
	std::array<std::string,8> letters = {{"a", "b", "c", "d", "e", "f", "g", "h"}};

	unsigned int xOrigin = getOrigin() % 8;
	unsigned int yOrigin = (getOrigin() / 8)+1;

	unsigned int xDestination = getDestination() % 8;
	unsigned int yDestination = (getDestination() / 8)+1;

	std::string promotionLetter = "";
	if(isPromotion())
	{
		unsigned int promotedType = getFlags() - Move::PROMOTION_FLAG +1;

		if(isCapture())
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