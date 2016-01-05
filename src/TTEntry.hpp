#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"

class TTEntry {

public:

	TTEntry()
{
}

	Move getBestmove() const {
		return bestmove;
	}

	int getDepth() const {
		return depth;
	}

	int getNodeType() const {
		return nodeType;
	}

	int getScore() const {
		return score;
	}

	Zkey getZkey() const {
		return zkey;
	}

private:

	Zkey zkey;
	int depth;
	int score;
	int nodeType; //TODO: add enum maybe
	Move bestmove;

};

#endif /* TTENTRY_HPP_ */
