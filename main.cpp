#include <iostream>
#include "Machine.h"
#include "Reel.h"

using namespace std;

void printMachine(int total, int cost, SlotMachine* sm) {
    cout << "----------------" << endl;
    cout << "| Slot Machine |" << endl;
    cout << "----------------" << endl;
    cout << "| " << sm->getR1prev();
    cout << "   " << sm->getR2prev();
    cout << "   " << sm->getR3prev() << " |" << endl;
    cout << "|> " << sm->getR1();
    cout << "   " << sm->getR2();
    cout << "   " << sm->getR3() << " <|" << endl;
    cout << "| " << sm->getR1next();
    cout << "   " << sm->getR2next();
    cout << "   " << sm->getR3next() << " |" << endl;
    cout << "----------------" << endl;
    cout << "| spin cost $" << cost << " |" << endl;
    cout << "| balance $"  << left << total << "|" << endl;
    cout << "----------------" << endl;
}

int main() {
    
    int total = 100; 
    const int cost = 1; 
    
    SlotMachine* sm = new SlotMachine();
   
    sm->spin();
    cout << "WELCOME TO THE CASINO" << endl;
    printMachine(total, cost, sm);
   
    int option = 0;
    while (option != 2) {
        cout << "Select option:" << endl;
        cout << "1. play" << endl;
        cout << "2. exit" << endl;
        cin >> option;
        if (option == 1) {
            if (total > cost) {
                sm->spin();
                int calculate = sm->calculate();
                if (calculate == 1000) {
                    cout << "JACKPOT!" << endl;
                }

                if (calculate <= 0) {
                    printMachine(total, cost, sm);
                    total = total + calculate;
                    total = total - cost;
                    cout << "---TRY AGAIN---" << endl;
                }
                else {

                    printMachine(total, cost, sm);
                    cout << "YOU WON $" << calculate << endl;
                    cout << "YOUR NEW BALANCE IS: $ " << total + calculate << endl;
                    total = total + calculate;
                    total = total - cost;
                }
            }

            else {
                cout << "YOUR BROKE" << endl;
            }
        }

    }
}