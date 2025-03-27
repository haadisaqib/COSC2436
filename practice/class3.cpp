#include <iostream>

using namespace std;


struct Node {
    int data;
    Node* next;

    Node(int d) {
        data = d;
        next = nullptr;
    }
};

int factorial(int x) {
    if (x == 1) {
        return 1;
    }

    int p = 1;
    for (int i = x; i > 1; i--) {
        p *= i;
    }
    return p;
}

int factorial_recursion(int x) {
    if (x == 1) {
        return 1;
    }
    return x * factorial_recursion(x - 1);
}



void printrec(Node* head) {
    if (head == nullptr) {
        return;
    }
    cout << head->data << " ";
    head = head -> next;
    printrec(head);

}

int main () {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    long int result = factorial(n);
    cout << "Factorial: " << result << endl;

    return 0;
}
