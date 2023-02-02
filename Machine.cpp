#include "Machine.h"
#include "Reel.h"
SlotMachine::SlotMachine() {
	// initialize all reels
	r1 = new Reel();
	r2 = new Reel();
	r3 = new Reel();
	
	// add data to each real
	r1->insert("A");
	r1->insert("B");
	r1->insert("C");
	r1->insert("7");
	r1->insert("A");
	r1->insert("B");
	r1->insert("C");
	r1->insert("7");
	r1->insert("A");
	r1->insert("A");
	// insert reel2
	r2->insert("A");
	r2->insert("B");
	r2->insert("C");
	r2->insert("7");
	r2->insert("A");
	r2->insert("B");
	r2->insert("C");
	r2->insert("7");
	r2->insert("A");
	r2->insert("B");
	// insert reel3
	r3->insert("C");
	r3->insert("A");
	r3->insert("B");
	r3->insert("C");
	r3->insert("7");
	r3->insert("A");
	r3->insert("B");
	r3->insert("C");
	r3->insert("7");
	r3->insert("A");
}

SlotMachine::~SlotMachine() {
	// destory each reel
	delete r1;
	delete r2;
	delete r3;
}




string SlotMachine::getR1prev() {
	return r1->head->prev->data;
}

string SlotMachine::getR1() {
	return r1->head->data;
}
string SlotMachine::getR1next() {
	return r1->head->next->data;
}

string SlotMachine::getR2prev() {
	return r2->head->prev->data;
}

string SlotMachine::getR2() {
	return r2->head->data;
}
string SlotMachine::getR2next() {
	return r2->head->next->data;
}

string SlotMachine::getR3prev() {
	return r3->head->prev->data;
}

string SlotMachine::getR3() {
	return r3->head->data;
}
string SlotMachine::getR3next() {
	return r3->head->next->data;
}

void SlotMachine::spin() {
	int roll = rand() % 100; 
	
	for (int i = 0; i < roll; i++) {
		r1->head = r1->head->next;
	}
	
	roll = rand() % 100;
	for (int i = 0; i < roll; i++) {
		r2->head = r2->head->next;
	}
	
	roll = rand() % 100;
	for (int i = 0; i < roll; i++) {
		r3->head = r3->head->next;
	}
}

int SlotMachine::calculate() {
	// get data from each reel
	string c1 = r1->head->data;
	string c2 = r2->head->data;
	string c3 = r3->head->data;

	if (c1 == c2 && c2 == c3) {
		if (c1 == "A") {
			return 10;
		}
		else if (c2 == "B") {
			return 25;
		}
		else if (c3 == "C") {
			return 150;
		}
		else {
			return 1000;
		}
	}
	else {
		return 0;
	}
}