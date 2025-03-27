#include <iostream>
#include <queue>
using namespace std;


bool guess(int profnb, int att = 1){
    int randomGuess = rand()%10;
    //base case
    if (profnb == randomGuess) {
        return true;
    }
    else {
        cout << randomGuess << endl;
        return guess(profnb, att+1);
    }
}

void reverseQueue(queue<int> line) {
    if (line.empty()) {
        return;
    }
    int front = line.front();
    line.pop();

    reverseQueue(line);

    line.push(front);
}

void printQueueRec(queue<int>& q){
    if (q.empty()) {
        return;
    }
    else {
        cout<< q.front() <<endl;
        q.pop();
        return printQueueRec(q);
    }
}


int main() {
    guess(10, 1);
    return 0;
}
