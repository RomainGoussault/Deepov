//============================================================================
// Name        : Deepov.cpp
// Author      : Romain Goussault
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Position.hpp"
using namespace std;

int main()
{
	cout << "!!!Hello World !!!" << endl;

	Position position(3, 4);
	Position deltaPosition = position.deltaX(10);

	cout << position.print() << endl;
	cout << deltaPosition.print() << endl;

	return 0;
}
