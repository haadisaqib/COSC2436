//331

//make a queue
//print a queue
//reverse a queue (recursive)

#include <iostream>
#include <queue>
using namespace std;

void printqueue(queue<int> q) {
    if (q.empty() || q.size() == 1) {
        return;
    }
    while (!q.empty()) {
        cout << q.front();
        q.pop();
    }
    cout<<endl;
}

queue<int> reverseQueue(queue<int>& line) {
    //2.base caseq.push(1);
    if (line.empty() || line.size() == 1) {
        return line;
    }
    
    //1.get everything into stack
    int s = line.front();
    line.pop();
    
    queue<int> q = reverseQueue(line);

    //3. take everything out
    line.push(s);

    //return
    return line;
}


int main() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    printqueue(q);
    reverseQueue(q);
    printqueue(q);
}