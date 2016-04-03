#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"

enum class NodeType {NONE, EXACT, LOWER, UPPER};

class TTEntry {

public:

	TTEntry() : myZkey(0), myDepth(0), myScore(0), myNodeType(NodeType::NONE), myBestMove()
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

    // TODO : store as bits to save mem space
	Zkey myZkey;
	int myDepth;
	int myScore;
	NodeType myNodeType;
	Move myBestMove;

};


inline std::ostream& operator<<(std::ostream &strm, const NodeType &node) {

        if (node == NodeType::NONE)
        {
            strm << "NONE" << " ";
        }
        else if (node == NodeType::EXACT)
        {
            strm << "EXACT" << " ";
        }
        else if (node == NodeType::LOWER)
        {
            strm << "LOWER" << " ";
        }
        else if (node == NodeType::UPPER)
        {
            strm << "UPPER" << " ";
        }

	return strm;
}

#endif /* TTENTRY_HPP_ */
