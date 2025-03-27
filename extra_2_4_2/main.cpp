#include <iostream>

using namespace std;

struct dll {
    int val;
    dll* next;
    dll* prev;
};

class d {
public:
    bool isPalindrome(dll* head, dll* tail);
};

bool d::isPalindrome(dll* head, dll* tail) {
    //base case
    if (!head || !tail || head == tail || head->next == tail) {
        return true;
    }

    //dont match
    if (head-> val != tail->val){
        return false;
    }
    //recursive case
    else {
        return isPalindrome(head->next, tail->prev);
    }   
}

int main() {
    // Creating a palindrome DLL: 1 <-> 2 <-> 3 <-> 2 <-> 1
    dll* node1 = new dll{1, nullptr, nullptr};
    dll* node2 = new dll{2, nullptr, node1};
    dll* node3 = new dll{3, nullptr, node2};
    dll* node4 = new dll{2, nullptr, node3};
    dll* node5 = new dll{1, nullptr, node4};

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;

    d palindromeChecker;
    if (palindromeChecker.isPalindrome(node1, node5)) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }

    // Clean up memory
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;

    return 0;
}