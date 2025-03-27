#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
};
//constru
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    return newNode;
}
void reverselistprint(Node* head) {
    //base case
    if (head == nullptr) {
        return;
    }
    //recursion
    reverselist(head->next);
    cout << head->data << endl;
}

Node* reverselist(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }
    if (head->next == nullptr) {
        return head;
    }

    //recursive call
    reverselist(head->next);
}

void printLL(Node* head) {
    //base case
}


int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    cout << "Original Linked List: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
    reverselist(head);
}