//QUEUE PRACTICE
#include <iostream>
#include <queue>

using namespace std;

struct st {
    int ps;
    st* next;
};

class q {
    private:
        st* front;
        st* back;
    
    public:
        q(){
            front = back = nullptr;
        }
        
        //check if empty
        bool isEmpty(st* cu){
            if (front == nullptr && back == nullptr){
                return true;
            }
            else {
                return false;
            }
        }
        
        //enqueue
        void enqueue(st* cu,int a) {
            //create ndoe
            st* temp = new st;

            //fill
            temp->ps = a;
            temp->next = nullptr;

            //link pointers
            //check if queue is empty
            if (isEmpty(cu)){
                front = back = temp;
            }
            else {
                back->next = temp;
                back = temp;
            }
        }

        //dequeue
        void dequeue(st* cu, int a){
            //check 
            st* temp;
            if (isEmpty(cu)) {
                return;
            } else {
                temp = front;
                a = temp->ps;
                if(front == back){  //nullptr
                    back = nullptr; 
                }
                front = front->next;
                delete temp;
            }
        }
        //search
        bool search(st* cu, int key) {
            st* temp = cu;
            if (isEmpty)
            if (temp->ps == key) {
                return true;
            }

        }
        
        //search recursive
        bool searchrec(st* cu, int key) {
        //base case
        if (cu == back) {
            return false;
        }
        //recursive case
        if (cu->ps == key) {
            return true;
        } else {
            return searchrec(cu->next, key);
        }
        }
        
        //print
        void print(st* cu) {
            if (isEmpty(cu)) {
                cout << "Queue is empty" << endl;
            }
            st* temp = cu;
            while (temp->next != nullptr) {
                cout << temp->ps << endl;
            }
        }
};


int main() {
    
}