#ifndef FASTMOVE_H
#define FASTMOVE_H

#include <iostream>

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

	strm << "Origin: " << fastmove.getOrigin() << " Dest: "
			<< fastmove.getDestination() << " Flags: " << fastmove.getFlags()
			<< std::endl;

	return strm;
}

#endif // FASTMOVE_H
