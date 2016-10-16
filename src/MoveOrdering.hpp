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

#ifndef MOVEORDERING_H_INCLUDED
#define MOVEORDERING_H_INCLUDED


#include "Board.hpp"
#include "MoveGen.hpp"
#include "Eval.hpp"
#include "Move.hpp"


class MoveOrdering
{
public :

    const static int KILLER1_BONUS = 20;
    const static int KILLER2_BONUS = 10;

    inline MoveOrdering() : myKiller1(), myKiller2() {}

    inline Move getKiller1(const unsigned int ply) const {return myKiller1[ply];}
    inline Move getKiller2(const unsigned int ply) const {return myKiller2[ply];}

    void setNewKiller(const Move& move,const unsigned int ply);
    void clearKillers();

    void rateMoves(std::vector<Move>& moveList, const unsigned int ply);
    void rateMoves(std::vector<Move>& moveList, std::shared_ptr<Board> board, const unsigned int ply, const bool isSee);
    void rateMovesH(std::vector<Move>& moveList, std::shared_ptr<Board> board, const unsigned int ply);

    void sortMoves(std::vector<Move>& moveList);
    std::vector<Move>::iterator getBestCandidate(std::vector<Move>& moveList);



private :
    // TODO : use MAX_DEPTH instead of 64
    Move myKiller1[64];
    Move myKiller2[64];
};

#endif // MOVEORDERING_H_INCLUDED
