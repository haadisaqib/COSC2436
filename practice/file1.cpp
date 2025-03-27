#include <iostream>

using namespace std;


void paws(int *A,int *B) {
    int temp = *A;
    *A = *B;
    *B = temp;
}

int main() {
  int* A = new int;
  int* B = new int;

  *A = 10;
  *B = 20;

    cout << "BEFORE SWAP" << *A << endl;
    cout << "BEFORE SWAP" << *B << endl;
  
  paws(A,B);

    cout << *A << endl;
    cout << *B << endl;

  delete A; 
  delete B; 

  return 0;
}