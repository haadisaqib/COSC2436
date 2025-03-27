#include <iostream>

using namespace std;

struct pearl {
    int color;
    pearl* hole;

    //constructor
    pearl(int c) {
        color = c;
        hole = nullptr;
    }
};

void insertAtbeg(pearl *&head, int color) {
    pearl* current = head;
    
    //construct new pearl
    pearl* toAdd = new pearl(color);

    //case1: add to beginning
    
}

void deleteFromBeg(pearl*& head, int &x) {
    pearl* current = head;
    x = current->color;
    head = current->hole;
    delete current;
}


void deleteFromEnd(pearl*& head) {
    pearl* current = head;

    //case1: list is empty
    if (head == nullptr) {
        return;
    }

    //case2: list of 1 pearl
    if (head->hole == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    
    while (current->hole->hole != nullptr) {
        current = current->hole;
    }

    delete current->hole;
    current->hole = nullptr;
}


void search() {

}

void print() {

}


int main() {


}