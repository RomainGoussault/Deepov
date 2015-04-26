#ifndef FASTMOVE_H
#define FASTMOVE_H

class FastMove
{

public:
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

#endif // FASTMOVE_H
