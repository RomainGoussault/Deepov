#include "catch.hpp"
#include "Uci.hpp"
#include "Board.hpp"
#include "Search.hpp"
#include "TT.hpp"


TEST_CASE( "Test uci command isready", "[isready]" )
{
	MagicMoves::initmagicmoves();
	Tables::init();
	
    Uci uci;
//  To verify default options    
//    uci.printOptions();
    
    SECTION("Test TT size during game and clear TT when rematch")
	{
        // Get hash size and converts to bytes to compare to globalTT
        int hash_value=std::stoi(uci.getOption("hash"));
        U64 ttSizeBytes = hash_value*1024*1024;
        
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

    
