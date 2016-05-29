#ifndef TT_HPP_
#define TT_HPP_

#include "Move.hpp"
#include "Types.hpp"
#include "TTEntry.hpp"

class TT {

public:

    const static U64 TT_SIZE = 10048576;

	TT()
    {
    }
    
    /* Overload access operator */
    inline TTEntry operator[](const U64 x) const {
        if( x > TT_SIZE ){std::cout << "TT out of bounds" <<std::endl;return myTTable[0];}
        return myTTable[x];
    };

    void setTTEntry(const Zkey zkey, const int depth, const int score, const NodeType node, const Move16 bestMove, const int moveCounter);
    TTEntry* probeTT(const Zkey zkey, const int depth);
    void clearTT()
    {
    	for(unsigned long int i=0; i<TT_SIZE; i++)
    	{
    		myTTable[i] = TTEntry();
    	}
    }

    U64 calculateEntryCount()
    {
    	U64 count = 0;
    	for(U64 i=0; i<TT_SIZE; i++)
    	{
    		count += myTTable[i].getNodeType() != NodeType::NONE;
    	}

    	return count;
    }


private:
    TTEntry myTTable[TT_SIZE];


};

extern TT globalTT;

inline std::ostream& operator<<(std::ostream &strm, const TT &tt) {

	for(unsigned long int entry = 0; entry < TT::TT_SIZE ; entry++)
	{
        if (tt[entry].getNodeType() != NodeType::NONE)
        {
		    strm << entry << " > ";
            strm << tt[entry].getNodeType() << " ";
		    strm << "Depth " << tt[entry].getDepth() << " ";
		    strm << "Score " << tt[entry].getScore() << " ";
		    strm << "Best move " << tt[entry].getBestmove() << " ";
		    strm << std::endl;
        }
	}
    strm << std::endl;
	return strm;
}


#endif /* TT_HPP_ */
