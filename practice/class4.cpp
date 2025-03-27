#include <iostream>
using namespace std;
void printRecArr(int arr[], int size, int index) {
    if (index == size) {
        return;
    }
    cout << arr[index] << " ";
    printRecArr(arr, size, index + 1);
}
int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = sizeof(arr) / sizeof(arr[0]);
    printRecArr(arr, size, 0);
    cout << endl;
    return 0;
}