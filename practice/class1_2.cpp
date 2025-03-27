#include <iostream>

using namespace std;

struct st {
    int id;
    float GPA;
    st *next;
};


//TODO 
void insertatx() {

}



bool searchgpa(st* cu, float key) {
    bool found = false;
    while (cu !=nullptr) {
        if (cu -> GPA = key) {
            cout << cu -> id << endl;
            found = true;
            return found;
        }
        cu = cu -> next;
    }
    if (cu = nullptr) {
        return false;
    }
}


void insertatstart(st*& head, int new_id, float new_GPA) {
    // Create a new node
    st* temp = new st;
    
    // Fill the new node with data
    temp->id = new_id;
    temp->GPA = new_GPA;
    
    // Update the pointer to point to the current head
    temp->next = head;
    
    // Update the head to point to the new node
    head = temp;

    //delete temp
    delete[] temp;
}

void insertatend (st*& head, int new_id, float new_GPA) {
    //create a new node
    st* temp = new st;

    temp -> id = new_id;
    temp -> GPA = new_GPA;
    temp -> next = nullptr;

    //traverse list and find end
    while (head ->next != nullptr) {
        head = head ->next;
        cout << head->id << endl;
    }
    if (head -> next = nullptr) {
        head -> next = temp;
    }

}z