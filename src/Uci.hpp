
#ifndef UCI_HPP_
#define UCI_HPP_

#include <vector>
#include <iostream>
#include <math.h>

#include "Board.hpp"
#include "Move.hpp"

//Uci documentation:
//http://wbec-ridderkerk.nl/html/UCIProtocol.html

class Uci
{
public :

	Uci()//Default constructor
	{
		boardPtr = std::shared_ptr<Board>(new Board());
	}

	void loop();

private:

	std::shared_ptr<Board> boardPtr;

	void updatePosition(std::istringstream& is);
	Move strToMove(std::string str);

};


#endif /* UCI_HPP_ */
