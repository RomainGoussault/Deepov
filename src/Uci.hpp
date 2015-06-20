
#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>
#include <thread>
#include <memory>
#include <chrono>
#include <ctime>
#include <ratio>



#include "Board.hpp"
#include "Move.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html

class Uci
{
public :

	Uci() : timeAllocated()
	{
		boardPtr = std::shared_ptr<Board>(new Board());
	}

	void loop();

private:

	std::shared_ptr<Board> boardPtr;
	std::thread myThread;
	int timeAllocated;

	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);
	void search();


};


#endif /* UCI_HPP_ */
