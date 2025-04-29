#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    set<int> people;
    for (int i = 1; i <= n; ++i)
        people.insert(i);

    auto it = people.begin();
    while (!people.empty()) {
        // Move to the next person (skip one)
        it++;
        if (it == people.end()) it = people.begin();
        cout << *it << " ";
        // Erase current person
        auto toErase = it++;
        if (it == people.end()) it = people.begin();
        people.erase(toErase);
    }

    return 0;
}
