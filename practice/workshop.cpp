#include <iostream>
#include <stack>
#include <string>

using namespace std;

int pre(char x) {
    switch(x) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void in_to_post(string exp) {
    stack<char> s;
    string result;
    int size_of_exp = exp.size();
    for (int i = 0; i < size_of_exp; i++) {
        int num = pre(exp[i]);
        if (num != 0) {
            
        }
    }
}

int main() {
    
}