//move kth to the front

#include <iostream>
#include <queue>

using namespace std;

void movekth(queue<int>& q, int k) {
    for (int i = 0; i < k; i++) {
        int front = q.front();
        q.pop();
        q.push(front);
    }
}

void printQueue(std::queue<int> q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(50);

    printQueue(q);

    movekth(q, 2);
    printQueue(q);
}