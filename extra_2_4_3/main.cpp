#include <iostream>

using namespace std;

//Double Linked ListD

// LL PRACTICE

struct dll {
    int val;
    dll* next;
    dll* prev;

    dll(int v) : val(v), next(nullptr), prev(nullptr) {}
};

//iteration
dll* reverseDll(dll* head) {
    if (head == nullptr || head->next == nullptr) return head;

    dll* cu = head;
    dll* temp = nullptr;

    // Traverse to the last node
    while (cu != nullptr) {
        // Swap prev and next pointers
        temp = cu->prev;
        cu->prev = cu->next;
        cu->next = temp;

        // Move to the next node 
        cu = cu->prev;
    }

    // Adjust head to point to the new first node
    if (temp != nullptr) {
        head = temp->prev;
    }

    return head;
}


dll* recursiveReverse(dll* head) {
    //base case
    if (!head || !head->next) {
        return head;
    }
    
    dll* temp = recursiveReverse(head->next);

    //swapping
    head->next->next = head;
    head->prev = head->next;
    head->next = nullptr;

    return temp;
}

int main() {

    return 0;
}