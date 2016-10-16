/*
    Deepov, a UCI chess playing engine.

    Copyright (c) 20014-2016 Romain Goussault, Navid Hedjazian

    Deepov is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Deepov is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Deepov.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TTENTRY_HPP_
#define TTENTRY_HPP_

#include "Move.hpp"
#include "Types.hpp"
#include "Utils.hpp"

enum NodeType {NONE=0, EXACT=1, LOWER=2, UPPER=3};

class TTEntry {

public:
    
    const static int K = 2;

	TTEntry() : myZkey(0), myBestMove(), myTTInfo(0), myTTvalue(0)
    {
    };


	inline TTEntry(Zkey zkey, int depth, int score, NodeType node, Move16 bestMove, int moveCounter) :
    myZkey(zkey), myBestMove(bestMove), myTTvalue(K*depth+moveCounter)
    {
        int sign = (score < 0);
        myTTInfo =((sign & 0x1) << 27 | (std::abs(score) & 0xfffff)<<7) | ((depth & 0x1f)<<2) | (node & 0x3);
    };

    inline Move16 getBestmove() const {
        return myBestMove;
    }

    inline int getTTValue() const {
        return myTTvalue;
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
	Zkey myZkey; // 
	Move16 myBestMove; // 16 bits : Flags 4 bits ||  Origin 6 bits ||  Destination 6 bits
    int myTTInfo; // 32 Bits : free : 5 bits || Score sign 1 bit || Score value 20 bits || Depth 5 bits || node type 2 bit
    int myTTvalue; // higher == should keep the value in TT. ttValue = k * depth + moveCounter with k integer to be tuned..
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

inline std::ostream& operator<<(std::ostream &strm, const TTEntry &entry) {

    strm << " > ";
    strm << entry.getNodeType() << " ";
    strm << "Depth " << entry.getDepth() << " ";
    strm << "Score " << entry.getScore() << " ";
    strm << "Best move " << Utils::Move16ToShortString(entry.getBestmove());
	return strm;
}

#endif /* TTENTRY_HPP_ */
