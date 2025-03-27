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

//insert at beg
void insertAtBeg(pearl*& head, int color) {
    pearl* toAdd = new pearl(color);
    pearl* current = head;

}


//insert at end

//insert based on node (color)

//insert at end

//delete from beg

//delete from end

//delete based on node color

//delete from index

//search based from off color (boolean found = true;)

//print