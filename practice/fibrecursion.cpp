#include <iostream>

using namespace std;

int fib(int n) {
    if (n<=1) return n;
    else return fib(n-1)+fib(n-2);
}

int main() {
    int n = 5;
    cout << "Fibonacci of " << n << " is: " << fib(n) << endl;
    return 0;
}