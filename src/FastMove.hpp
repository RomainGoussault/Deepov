#ifndef FASTMOVE_H
#define FASTMOVE_H

#include <iostream>
#include <bitset>

class FastMove
{

public:

	const static unsigned int CAPTURE_FLAG = 0b0100;

	FastMove(unsigned int origin, unsigned int destination, unsigned int flags)
	{
		myMove = ((flags & 0xf)<<12) | ((origin & 0x3f)<<6) | (destination & 0x3f);
	}

	unsigned int getDestination() const {
		return myMove & 0x3f;
	}
	unsigned int getOrigin() const {
		return (myMove >> 6) & 0x3f;
	}
	unsigned int getFlags() const {
		return (myMove >> 12) & 0x0f;
	}

private:
	int myMove; //Bits : Flags 4 bits ||  Origin 6 bits ||  Destination (6 bits)

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
