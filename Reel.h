
#ifndef REEL
#define REEL
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node* prev;
    Node(string t) {
        data = t;
        next = this;
        prev = this;
    }
};
class Reel {
private:


public:
    Node* head; 
    Reel();
    ~Reel();
    void insert(string value);

};




#endif