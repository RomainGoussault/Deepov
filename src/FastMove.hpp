#ifndef FASTMOVE_H
#define FASTMOVE_H
#include <string>
#include "Player.hpp"
#include "Board.hpp"

class FastMove {
public:
	FastMove(unsigned int from, unsigned int to, unsigned int flags);
	unsigned int getTo() const {
		return myMove & 0x3f;
	}
	unsigned int getFrom() const {
		return (myMove >> 6) & 0x3f;
	}
	unsigned int getFlags() const {
		return (myMove >> 12) & 0x0f;
	}

private:
	int myMove;

};

#endif // FASTMOVE_H
