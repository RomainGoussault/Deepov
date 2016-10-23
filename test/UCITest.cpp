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
#include "Uci.hpp"
#include "Board.hpp"
#include "Search.hpp"
#include "TT.hpp"


TEST_CASE( "Test uci command isready", "[isready]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	ZK::initZobristKeys();
    globalTT.init_TT_size(TT::TEST_MB_SIZE);
	
    Uci uci;
//  To verify default options    
//    uci.printOptions();
    
    SECTION("Test TT size during game and clear TT when rematch")
	{       
	    uci.initSearch();
	    U64 maxEntries = globalTT.getTTSize();
	    U64 nEntries = globalTT.countEntries();
	    REQUIRE(nEntries == 0);
	    
	    Search uciSearch = uci.getUciSearch();
	    uciSearch.negaMaxRootIterativeDeepening(1000);
	    nEntries = globalTT.countEntries();
	    REQUIRE(nEntries > 0);
	    
	    // Test clear TT
	    uci.newGame();
	    nEntries = globalTT.countEntries();
	    REQUIRE(globalTT.getTTSize() == maxEntries);
	    REQUIRE(globalTT.countEntries() == 0);
	}
}

    
