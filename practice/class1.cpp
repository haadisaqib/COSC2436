#include <iostream>

using namespace std;

struct st {
    int id;
    float GPA;
    st *next;
};

int main() {
    // st john;
    // st *p = new st; //alloc with no name

    // p->id = 123;
    // p->GPA = 4.0; // first node
    // p->next = 0;
    
    // p = p->next;   // p = p-> next 
    // p = new st;   // p = new st;

    // p->next->id = 321;
    // p->next->GPA = 3.9; //second node
    // p->next->next = 0;

    // p->next->next = new st;


    //--------------------------


    st *head;
    st *q;

    q = new st;
    head = q;
    for (int i = 0; i<3; i++) {
        q->id = rand()%10;
        q->GPA = rand()%4;
        q->next = nullptr;

        //create a new node
        q = q->next;
        q = new st;

    }
    q -> id = 123;
    q -> GPA = 4.;
    q ->next = nullptr; 
	
    //----PRINT LL
    while (q->next != nullptr) {
        q = q->next;
        cout << q->id << endl;
    }
}



