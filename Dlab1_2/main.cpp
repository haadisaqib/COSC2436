#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    int x;
    cin >> x;

    vector<int> arr(x);

    //init set
    set<int> set;

    //inserting elements into arr
    for(int i=0;i<x;i++){
        cin>>arr[i];
    }

    sort(arr.begin(),arr.end());

    //use a set to store unique elements in arr
    for (int i = 0; i < x; i++) {
        if (set.find(arr[i]) == set.end()){
            set.insert(arr[i]);
        }
    }
    //write a new

    int counter = set.size();
    cout << counter << endl;

    return 0;
}