#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"

enum class NodeType {EXACT, LOWER, UPPER};

class TTEntry {

public:

	TTEntry()
    {
    }

	inline TTEntry(Zkey zkey, int depth, int score, NodeType node, Move bestMove) :
    myZkey(zkey), myDepth(depth), myScore(score), myNodeType(node), myBestMove(bestMove)
    {
    };

	inline Move getBestmove() const {
		return myBestMove;
	}

	inline int getDepth() const {
		return myDepth;
	}

	inline NodeType getNodeType() const {
		return myNodeType;
	}

	inline int getScore() const {
		return myScore;
	}

	inline Zkey getZkey() const {
		return myZkey;
	}

private:

	Zkey myZkey;
	int myDepth;
	int myScore;
	NodeType myNodeType;
	Move myBestMove;

};

#endif /* TTENTRY_HPP_ */
