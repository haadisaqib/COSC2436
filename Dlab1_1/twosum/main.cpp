#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    // x = size of arr
    // n = target sum

    int x, n;
    cin >> x >> n;
    int arr[x] = {};

    //declare hashmap
    unordered_map<int, int> map; 

    //place inputs into array
    for (int i=0; i<x; ++i) {
        cin >> arr[i];
    }

    //iterate through array and if curr element - target sum is in hashmap, print the index of the element and the index of the element in the hashmap
    for (int i=0; i<x; ++i) {
        if (map.find(n - arr[i]) != map.end()) {
            cout << map[n - arr[i]] + 1 << " " << i + 1 << endl;
            return 0;
        }
        map[arr[i]] = i;
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;

}