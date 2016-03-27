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



