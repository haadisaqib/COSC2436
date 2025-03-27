#include <iostream>
#include <queue>
#include <stack>
// #include <queue>

using namespace std;
//sort a stack using an additional stack


void operation(stack<int>& s, queue<int>& q) {
    //edge case
    if(q.empty()) return;
    int size = q.size();
    //not empty
    for (int i = 0; i < size; i++) {
        if(q.front()%2==0) {          //is even
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
        else {                  //is odd
            int odd_to_push = q.front();
            s.push(odd_to_push);
            q.pop();
        }
        return;
    }
}





int main() {
    return 0;
}