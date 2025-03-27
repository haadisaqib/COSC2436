#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// example:
// input: 5 3 2 8 1
// output: 3rd largest element is 3
// sort: 1 2 3 5 8

int kthlargest(vector<int>& arr, int size, int k) {
    if (k > size) return -1;
    sort(arr.begin(), arr.end());
    int diff = size - k;
    return arr[diff+1];
}

int main () {
    vector<int> arr = {10,11,5,7,4,15,3,20};
    int res = kthlargest(arr, arr.size(), 3);
    cout << res << endl;
    return 0;
}