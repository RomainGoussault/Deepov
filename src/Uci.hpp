
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

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html
typedef std::map<std::string, UciOption> OptionsMap;



class Uci
{
public :

	Uci() : wtime(1000), btime(1000), winc(1000), binc(1000)
	{
		myBoardPtr = std::shared_ptr<Board>(new Board());

		//Init Options map
		myOptionsMap["timeDivider"] = UciOption("50", "spin");
	}

	void loop();

private:

	std::shared_ptr<Board> myBoardPtr;
	thrd::thread myThread;
	unsigned int wtime;
	unsigned int btime;
	unsigned int winc;
	unsigned int binc;

	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);
	void search();
	void setoption(std::istringstream& is);
	void printOptions() const;
	std::string getOption(const std::string str) const;

	OptionsMap myOptionsMap;

};


#endif /* UCI_HPP_ */
