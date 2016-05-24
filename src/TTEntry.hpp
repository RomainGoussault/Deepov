#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"

enum NodeType {NONE=0, EXACT=1, LOWER=2, UPPER=3};

class TTEntry {

public:

	TTEntry() : myZkey(0), myBestMove(), myTTInfo(0)
    {
    }

	inline TTEntry(Zkey zkey, int depth, int score, NodeType node, Move bestMove) :
    myZkey(zkey), myBestMove(bestMove.getMove())
    {
        int sign = (score < 0);
        myTTInfo =((sign & 0x1) << 27 | (std::abs(score) & 0xfffff)<<7) | ((depth & 0x1f)<<2) | (node & 0x3);
    };

	inline Move getBestmove() const {
		return Move(myBestMove);
	}

	inline int getDepth() const {
		return (myTTInfo >> 2) & 0x1f;
    }

	inline NodeType getNodeType() const {
		return static_cast<NodeType>(myTTInfo & 0x3);
	}

	inline int getScore() const {
        int sign = (myTTInfo >> 27) & 0x1 ;
		return (1-2*sign)*((myTTInfo >> 7) & 0xfffff); // (1-2*sign)*abs(score)
	}

	inline Zkey getZkey() const {
		return myZkey;
	}

private:

    // TODO : store as bits to save mem space
	Zkey myZkey;
	unsigned int myBestMove;
    int myTTInfo; // 32 Bits : free : 5 bits || Score sign 1 bit || Score value 20 bits || Depth 5 bits || node type 2 bit


};

/* myTTInfo details  

NodeType :  0 = NONE, 1 = EXACT, 2 = LOWER, 3 = UPPER
Depth : 5 bits -> depth up to 32
Score : 21 bits -> score -1 048 576 up to 1 048 576 (max score is 1 000 000)

*/

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
