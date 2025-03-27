#include <iostream>
#include <chrono>
#include <cstdlib>   
#include <ctime>     

using namespace std;

// Insertion Sort
void insertionSort(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements that are greater than key to one position ahead
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Shell Sort with gap = 19
void shellSortGap19(int arr[], int size) {
    int gap = 19;  
    // If the array is smaller than 19, the loop will still do an insertion-like pass with gap=19.
    while(gap > 0) {
        for(int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;

            // Compare elements gap distance apart
            while(j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        if(gap == 19) {
            gap = 1;  
        } else {
            break;
        }
    }
}

int main() {
    const int SIZE = 500;
    int arr1[SIZE], arr2[SIZE];

    // Seed random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    // Generate 500 random numbers in arr1
    for(int i = 0; i < SIZE; i++) {
        arr1[i] = rand() % 10000;  // random integers from 0 to 9999
    }

    // Make a copy of arr1 into arr2 so both sorts have the same initial data
    for(int i = 0; i < SIZE; i++) {
        arr2[i] = arr1[i];
    }

    // -------------------------
    // Insertion Sort Timing
    // -------------------------
    auto startInsertion = chrono::high_resolution_clock::now();
    insertionSort(arr1, SIZE);
    auto endInsertion = chrono::high_resolution_clock::now();
    auto insertionDuration = chrono::duration_cast<chrono::microseconds>(endInsertion - startInsertion).count();


    auto startShell = chrono::high_resolution_clock::now();
    shellSortGap19(arr2, SIZE);
    auto endShell = chrono::high_resolution_clock::now();
    auto shellDuration = chrono::duration_cast<chrono::microseconds>(endShell - startShell).count();

    // Print 
    cout << "Insertion Sort took: " << insertionDuration << " microseconds." << endl;
    cout << "Shell Sort (gap=19) took: " << shellDuration << " microseconds." << endl;

    // Compare 
    if (insertionDuration < shellDuration) {
        cout << "Insertion Sort was faster." << endl;
    } else if (shellDuration < insertionDuration) {
        cout << "Shell Sort (gap=19) was faster." << endl;
    } else {
        cout << "Both sorts took exactly the same time (unlikely, but possible!)." << endl;
    }

    return 0;
}
