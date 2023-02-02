#pragma once
#include <string>
#include "Reel.h"

using namespace std;

Reel::Reel() {
    // initialize data members
    head = nullptr;
}

Reel::~Reel() {
    // create a iterator
    Node* itr = head;
    while (itr != nullptr) {
        head = head->next; // move head to next node
        delete itr; // delete current node
        itr = head;
    }
}

void Reel::insert(string c) {
    
    if (head == nullptr) {
       
        head = new Node(c);
    }
    else {
       
        Node* n = new Node(c);
        
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
        // reassign head
        head = n;
    }
}
