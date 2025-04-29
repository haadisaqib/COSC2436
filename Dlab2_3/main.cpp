#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<tuple<int, int, int>> ranges(n); // a, b, index

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        ranges[i] = {a, b, i};
    }

    // Sort by a ascending, b descending
    sort(ranges.begin(), ranges.end(), [](auto &x, auto &y) {
        if (get<0>(x) == get<0>(y)) return get<1>(x) > get<1>(y);
        return get<0>(x) < get<0>(y);
    });

    vector<int> contains(n), contained(n);
    int max_b = 0;
    for (auto &[a, b, idx] : ranges) {
        if (b <= max_b) contained[idx] = 1;
        max_b = max(max_b, b);
    }

    int min_b = INT_MAX;
    for (int i = n - 1; i >= 0; --i) {
        auto [a, b, idx] = ranges[i];
        if (b >= min_b) contains[idx] = 1;
        min_b = min(min_b, b);
    }

    for (int x : contains) cout << x << " ";
    cout << "\n";
    for (int x : contained) cout << x << " ";
    cout << "\n";
}
