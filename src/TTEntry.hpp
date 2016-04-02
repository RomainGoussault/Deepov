#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"

enum class NodeType {EXACT, LOWER, UPPER}

class TTEntry {

public:

	TTEntry()
{
}

	Move getBestmove() const {
		return myBestBove;
	}

	int getDepth() const {
		return depth;
	}

	NodeType getNodeType() const {
		return myNodeType;
	}

	int getScore() const {
		return myScore;
	}

	Zkey getZkey() const {
		return myZkey;
	}

private:

	Zkey myZkey;
	int myDepth;
	int myScore;
	NodeType myNodeType;
	Move myBestBove;


};

#endif /* TTENTRY_HPP_ */
