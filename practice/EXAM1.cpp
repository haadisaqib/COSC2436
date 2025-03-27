//write a bunch of functions
#include <iostream>
using namespace std;

struct node {
    int val;
    node* next;

    node() {
        val = 0;
        next = nullptr;
    }

};

//insert node at the end of list
void insertatend(node*& head){
    node* newHead = new node();
    //edge
    if (head == nullptr) {
        node* newHead = new node();
        head = newHead;
        return;
    }
    node* cu = head;
    while (cu->next != nullptr) {
        cu = cu->next;
    }
    cu->next = newHead;
    return;
}
//insert at beginning of list
void insertatbeg(node*& head){
    node* newhead = new node();
    head = newhead;
    return;
}

node* mergelist(node* head1, node* head2) {
    //edge
    if (head1 == nullptr) {
        return head2;
    }
    if (head2 == nullptr) {
        return head1;
    }    //recursive
    if (head1->val<head2->val) {
        head1->next = mergelist(head1->next, head2);
        return head1;
    } else {
        head2->next = mergelist(head1, head2->next);
        return head2;
    }
}




//delete from beginning of list
void delbeg(node* head) {
    if (head==nullptr) {
        return;
    }

    node* temp = head;
    head = head->next;
    delete temp;
}

//delete from end of list
void deletefrmend(node*& head) {
    if (head == nullptr) {
        return;
    }
    if (head -> next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    node* cu = head;
    while (cu->next->next != nullptr) {
        cu = cu->next;
    }
    delete cu->next;
    cu->next = nullptr;
    return;
}

//recursive functions
//printrev recursivly
void printrevll(node* head) {
    if (head == nullptr) {
        return;
    }
    printrevll(head->next);
    cout << head->val << endl;
}

//is palindrome
bool ip(string arr[], int left, int right){
    //base case
    if (left >= right) {
        return true;
    }

    if (arr[left] != arr[right]) {
        return false;
    }

    return ip(arr, left + 1, right - 1);
}

int main() {

}