#include <iostream>
using namespace std;

void bubbleSort(int arr[], int n) {
    int s = 0;
    int temp;
    for(int i = n-1, i >= 1; i--) {
        for(int j = 0; j <= i-1; j++) {
            temp++;
            if(arr[j] > arr[j+1]) {
                s++;
                swap(arr[j], arr[j+1]);
            }
}


int main() {



}