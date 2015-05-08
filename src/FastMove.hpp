#ifndef FASTMOVE_H
#define FASTMOVE_H

#include <iostream>
#include <bitset>

class FastMove
{

public:

	const static unsigned int CAPTURE_FLAG = 0b0100;
	const static unsigned int PROMOTION_FLAG = 0b1000;

	FastMove(unsigned int origin, unsigned int destination, unsigned int flags)
	{
		myMove = ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
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

    inline void setDestination(unsigned const int& destination)
    {
        myMove &= ~0x3f; myMove |= destination & 0x3f;
    }
    inline void setOrigin(unsigned const int& origin)
    {
        myMove &= ~0xfc0; myMove |= ((origin & 0x3f) << 6);
    }

	inline void setFlag(unsigned const int& flag)
	{
	    myMove &= 0xfff; myMove |= ((flag & 0x3f) << 12);
	}

private:

	int myMove; //Bits : Flags 4 bits ||  Origin 6 bits ||  Destination 6 bits
	/* The MSB of the flags is the promotion bit, the bit after is the capture bit.
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
