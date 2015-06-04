#ifndef FASTMOVE_H
#define FASTMOVE_H

#include <iostream>
#include <bitset>
#include <string>
#include <array>

class FastMove
{

public:
    const static unsigned int EPCAPTURE_FLAG = 0b0101;
    const static unsigned int DOUBLEPAWNPUSH_FLAG =0b0001;
	const static unsigned int CAPTURE_FLAG = 0b0100;
	const static unsigned int PROMOTION_FLAG = 0b1000;
	const static unsigned int PAWN_TYPE = 0;
	const static unsigned int KNIGHT_TYPE = 1;
	const static unsigned int BISHOP_TYPE = 2;
	const static unsigned int ROOK_TYPE = 3;
	const static unsigned int QUEEN_TYPE = 4;
	const static unsigned int KING_TYPE = 5;

	/*inline FastMove(unsigned int origin, unsigned int destination, unsigned int flags)
	{
		myMove = ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
	}*/

	inline FastMove(unsigned int origin, unsigned int destination, unsigned int flags,unsigned int pieceType)
	{
		myMove = ((pieceType &0x7)<<16) | ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
	}

	inline unsigned int getDestination() const
	{
		return myMove & 0x3f;
	}

	inline unsigned int getOrigin() const
	{
		return (myMove >> 6) & 0x3f;
	}

	inline unsigned int getFlags() const
	{
		return (myMove >> 12) & 0x0f;
	}

	inline unsigned int getPieceType() const
	{
		return (myMove >> 16) & 0x7;
	}

    inline unsigned int getCapturedPieceType() const
	{
		return (myMove >> 19) & 0x7;
	}

    inline void setDestination(unsigned const int destination)
    {
        myMove &= ~0x3f; // clear the first 6 bits
        myMove |= (destination & 0x3f); // mask on the first 6 bits and OR it with myMoves
    }

    inline void setOrigin(unsigned const int origin)
    {
        myMove &= ~0xfc0; myMove |= ((origin & 0x3f) << 6);
    }

	inline void setFlags(unsigned const int flag)
	{
	    myMove &= ~0xf000; myMove |= ((flag & 0x3f) << 12);
	}

    inline void setCapturedPieceType(unsigned const int type)
	{
	    myMove &= ~0x380000; myMove |= ((type & 0x3f) << 19);
	}

	inline bool isCapture() const {return getFlags() & CAPTURE_FLAG;}
	inline bool isPromotion() const {return getFlags() & PROMOTION_FLAG;}

	std::string toShortString() const
	{
		std::array<std::string,8> letters = {{"a", "b", "c", "d", "e", "f", "g", "h"}};

		int xOrigin = getOrigin() % 8;
		int yOrigin = (getOrigin() / 8)+1;

		int xDestination = getDestination() % 8;
		int yDestination = (getDestination() / 8)+1;

		std::stringstream ss;
		ss << letters[xOrigin] << yOrigin << letters[xDestination] << yDestination;

		return ss.str();
	}

private:

	int myMove; //Bits : Captured Piece 3 bits || Piecetype 3 bits || Flags 4 bits ||  Origin 6 bits ||  Destination 6 bits
	/*
	 * PieceType:
	 * 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen, 5 King
	 * For captured piece 0 Pawn, 1 Knight, 2 Bishop, 3 Rook, 4 Queen
	 *
	 * Flags:
	 * The MSB of the flags is the promotion bit, the bit after is the capture bit.
	 * All the possibles flags combinations are represented below:
		0	0	0	0	quiet moves
		0	0	0	1	double pawn push
		0	0	1	0	king castle
		0	0	1	1	queen castle
		0	1	0	0	captures
		0	1	0	1	ep-capture
		1	0	0	0	knight-promotion
		1	0	0	1	bishop-promotion
		1	0	1	0	rook-promotion
		1	0	1	1	queen-promotion
		1	1	0	0	knight-promo capture
		1	1	0	1	bishop-promo capture
		1	1	1	0	rook-promo capture
		1	1	1	1	queen-promo capture
	*/
};


inline std::ostream& operator<<(std::ostream &strm, const FastMove &fastmove) {

	std::bitset<4> flags(fastmove.getFlags());
	int xOrigin = fastmove.getOrigin() % 8;
	int yOrigin = fastmove.getOrigin() / 8;

	int xDestination = fastmove.getDestination() % 8;
	int yDestination = fastmove.getDestination() / 8;

	strm << "Origin: [" << xOrigin << ", " << yOrigin << "] Dest: ["
			<< xDestination << ", " << yDestination << "] Flags: " << flags
			<< std::endl;

	return strm;
}

#endif // FASTMOVE_H
