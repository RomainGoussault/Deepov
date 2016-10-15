
#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>
#include <memory>
#include <chrono>
#include <ctime>
#include <ratio>
#include <map>
#include <thread>


namespace thrd = std;

#include "Board.hpp"
#include "Move.hpp"
#include "UciOption.hpp"
#include "TT.hpp"
#include "Types.hpp"
#include "Search.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html
typedef std::map<std::string, UciOption> OptionsMap;



class Uci
{
public :

	Uci() : wtime(1000), btime(1000), winc(1000), binc(1000), myBoardPtr(std::shared_ptr<Board>(new Board())), mySearch(Search(myBoardPtr))
	{
		// myBoardPtr(std::shared_ptr<Board>(new Board()));
		// mySearch(Search(myBoardPtr));

		//Init Options map
		myOptionsMap["timeDivider"] = UciOption("50", "spin",1,1000);
		myOptionsMap["positionnalGain"] = UciOption("100", "spin",1,1000);
		myOptionsMap["mobilityGain"] = UciOption("100", "spin",1,1000);
		myOptionsMap["pawnGain"] = UciOption("100", "spin",1,1000);
		myOptionsMap["hash"] = UciOption("16", "spin",1,2048); //hash size in MB
	}

	void loop();
	void init();
    void setoption(std::istringstream& is);
    void printOptions() const;
    void initSearch();
    void newGame();
    std::string getOption(const std::string str) const;

    // get methods    
    inline Search getUciSearch() const {return mySearch;}

private:

	unsigned int wtime;
	unsigned int btime;
	unsigned int winc;
	unsigned int binc;
	std::shared_ptr<Board> myBoardPtr;
	Search mySearch;
	thrd::thread myThread;


	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);
	void search();

	OptionsMap myOptionsMap;

};


#endif /* UCI_HPP_ */
