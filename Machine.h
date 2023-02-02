#pragma once
#include "Reel.h"
#include <iostream>
#include <string>
class SlotMachine {
private:
	Reel* r1; // reel 1, left reel
	Reel* r2; // real 2, middle reel
	Reel* r3; // reel 3, right reel
public:
	SlotMachine();
	~SlotMachine(); 
	void spin(); 
	int calculate(); 
	string getR1prev(); 
	string getR1(); 
	string getR1next(); 
	string getR2prev(); 
	string getR2();
	string getR2next();
	string getR3prev(); 
	string getR3();
	string getR3next(); 
};
