#include <iostream>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Use a multiset to store available ticket prices
    multiset<int> tickets;
    for (int i = 0; i < n; i++) {
        int price;
        cin >> price;
        tickets.insert(price);
    }
    
    for (int i = 0; i < m; i++) {
        int bid;
        cin >> bid;
        
        // Find the first ticket with a price greater than bid
        auto it = tickets.upper_bound(bid);
        
        // If no ticket with price <= bid exists, output -1
        if (it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            it--;
            cout << *it << "\n";
            tickets.erase(it);  
        }
    }
    
    return 0;
}
