#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

int countrec(Node*& head) { 
    Node* current = head; 
    if (current == nullptr) { 
        return 0; 
    } 
    else { 
        return 1 + countrec(current->next); 
    }
}

void printrec(Node* head) { 
    if (head == nullptr) { 
        cout << "List is empty" << endl; 
        return;
    }
    Node* current = head; 
    while (current != nullptr) {
        cout << current->data << " "; 
        current = current->next;
    }
    cout << endl;
}

void recursiveprintreverse(Node*& head) {
    Node* current = head; 
    if (current == nullptr) { 
        return;
    } 
    recursiveprintreverse(current->next);
    cout << current->data << " "; 
}

bool searchrec(Node*& head, int key) { 
    Node* current = head; 
    if (current == nullptr) { 
        return false; 
    } 
    else if (current->data == key) { 
        return true; 
    } 
    else { 
        return searchrec(current->next, key); 
    }
}

int main() {
    Node* head = new Node; 
    head->data = 1; 
    head->next = new Node;
    head->next->data = 2; 
    head->next->next = new Node;
    head->next->next->data = 3; 
    head->next->next->next = nullptr;
    int numInList = countrec(head); 
    bool search = searchrec(head, 2); 
    printrec(head);
    return 0; 
}