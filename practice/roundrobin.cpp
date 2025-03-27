#include <iostream>
#include <queue>

using namespace std;

struct process{
    string processID;
    int time;

    process() {} // default constructor
    process(string ID, int time): processID(ID), time(time) {}
};


bool hasRemaining(process arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i].time != -1) {
            return true;
        }
    }
    return false;
}


void round_robin(process arr[], int n, int time, queue<string>& q) {
    while(hasRemaining(arr, n)){
        for (int i = 0; i < n; i++) {
            if (arr[i].time == -1) {
                continue;
            }
            if (arr[i].time <= time) {
                string ID = arr[i].processID;
                q.push(ID);
                arr[i].time = -1;
            }
            else if (arr[i].time > time) {
                arr[i].time -= time; 
            }
        }
    }
}

void printqueue(queue<string>& q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
}

int main() {
    const int SIZE = 100000;
    process p[SIZE];
    queue<string> q; // queue to store the order of execution

    srand(time(0)); // Seed the random generator

    for (int i = 0; i < SIZE; ++i) {
        int randID = rand() % 100; // random number for ID
        int randTime = rand() % 9901 + 100; // random time between 100 and 10000
        p[i] = process("P" + to_string(randID), randTime);
    }

    //run round robin algorithm
    int quantum = 500;
    round_robin(p, SIZE, quantum, q);
    cout << endl;
    cout << "Remaining processes: ";
    printqueue(q);
    cout << endl;

    return 0;
}