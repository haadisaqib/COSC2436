#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int maxDistance(vector<int> &st, int end){
    //edge case 1
    if (st.size() == 2) {
        return end;
    }
    int winner;
    for (int i = 0; i<st.size()-1; i++) {
        int res = st[i+1] - st[i];
        if (i == 0) {
            winner = res;
        }
        winner = max(winner,res);
    }
    return winner;
}

int main() {
    //NEED SPPED
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    //x is len, n is traffic lights
    int x, n;
    cin >> x >> n;

    //intilize list 
    vector<int> lightPositions;
    for (int i=0; i<n; i++) {
        int position;
        cin >> position;
        lightPositions.push_back(position);
    }

    //make street
    vector<int> street{0};
    street.push_back(x);

    //add light to street
    for (auto position : lightPositions){
        street.push_back(position);
        sort(street.begin(), street.end());
        int distance = maxDistance(street, x);
        cout << distance << " ";
    }
}