
#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>
#include <boost/thread.hpp>
#include <memory>
#include <chrono>
#include <ctime>
#include <ratio>

namespace thrd = boost;

#include "Board.hpp"
#include "Move.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html

class Uci
{
public :

	Uci() : wtime(1000), btime(1000), winc(1000), binc(1000)
	{
		boardPtr = std::shared_ptr<Board>(new Board());
	}

	void loop();

private:

	std::shared_ptr<Board> boardPtr;
	thrd::thread myThread;
	int wtime;
	int btime;
	int winc;
	int binc;

	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);
	void search();

};


#endif /* UCI_HPP_ */
