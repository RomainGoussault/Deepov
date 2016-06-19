#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include <unordered_map>

#include "Board.hpp"
#include "MoveGen.hpp"
#include "MoveOrdering.hpp"
#include "Eval.hpp"
#include "TTEntry.hpp"


class Search
{
public:
	constexpr static int MAX_DEPTH = 64;
	Search(std::shared_ptr<Board> boardPtr);

    void clearSearchData();

    int negaMaxRoot(const int depth);
    int negaMaxRootIterativeDeepening(const int timeSec);
    inline int getCurrentScore() {return myEval.evaluate();};
    bool isInsufficentMatingMaterial() const;
    Move16 myBestMove;

    // Display 
    U64 myMovesSearched; // TODO Count nodes not moves
    inline Move getPVMove(const unsigned int ply, const unsigned int depth) const {return myPvTable[ply][depth];}
    void printPvTable(const unsigned numLines);

private:

    std::shared_ptr<Board> myBoard;
    Eval myEval;
    MoveOrdering myMoveOrder;
    unsigned int myPly;

    int negaMax(const int depth, int alpha, const int beta);
    int negaMax(const int depth, int alpha, const int beta, const bool isNullMoveAuth);
    int evaluate();
    int qSearch(int alpha, const int beta);

    Move myPvTable[MAX_DEPTH][MAX_DEPTH]; // Quadratic PV-table
    unsigned int myPvLength[MAX_DEPTH]; // Length of the PV line at this ply 

    /* pvtable[ply as distance from root][depth of the line] Quadratic PV-Table
    
    ply  maxLengthPV
        +--------------------------------------------+
    0   |N                                           | pvtable[0][0:N]
        +--------------------------------------------+
    1   +-|N-1                                       | pvtable[1][0:N-1]
        +--------------------------------------------+
    2   +-+-|N-2                                     | pvtable[2][0:N-2]
        +--------------------------------------------+
    etc

    We stop the pv at null moveCounter

    maxPVlength = N - ply

    // TODO : fix conflict with hashtable to save the full PV line
    */
};

#endif // SEARCH_H_INCLUDED
