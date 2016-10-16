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

#include "catch.hpp"
#include "Board.hpp"
#include "Search.hpp"
#include "TT.hpp"

TEST_CASE( "Retrieve the principal variation", "[pv]" )
{
//    std::shared_ptr<Board> sp = std::shared_ptr<Board>(new Board("3k4/3r4/3r4/3q4/3R4/3R4/3Q4/3K4 w - - 0 1"));
//    std::cout << *sp << std::endl; 
//    Search search(sp);
//	search.negaMaxRoot(5);
//    search.printPvTable(1);
//    search.printPvTable(2);
//    search.printPvTable(5);

//    search.negaMaxRoot(7);
//    search.printPvTable(5);
}

