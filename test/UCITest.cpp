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
	    globalTT.clearTT();
        nEntries = globalTT.countEntries();
	    REQUIRE(globalTT.getTTSize() == maxEntries);
	    REQUIRE(globalTT.countEntries() == 0);
	}
}

    
