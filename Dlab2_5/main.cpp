#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Customer {
    int arrival;
    int departure;
    int id;
};

bool compareCustomers(const Customer& a, const Customer& b) {
    return a.arrival < b.arrival;
}

int main() {
    int n;
    cin >> n;

    vector<Customer> customers(n);
    for (int i = 0; i < n; ++i) {
        cin >> customers[i].arrival >> customers[i].departure;
        customers[i].id = i;
    }

    sort(customers.begin(), customers.end(), compareCustomers);

    set<pair<int, int>> available_rooms; // {departure_time, room_number}
    vector<int> room_assignment(n);
    int rooms_needed = 0;
    int room_counter = 1;

    for (const auto& customer : customers) {
        auto it = available_rooms.lower_bound({customer.arrival, 0});

        if (it != available_rooms.begin()) {
            it--;
            if (it->first <= customer.arrival) {
                room_assignment[customer.id] = it->second;
                available_rooms.erase(it);
                available_rooms.insert({customer.departure, room_assignment[customer.id]});
            } else {
                room_assignment[customer.id] = room_counter;
                available_rooms.insert({customer.departure, room_counter});
                rooms_needed = max(rooms_needed, room_counter);
                room_counter++;
            }
        } else {
            room_assignment[customer.id] = room_counter;
            available_rooms.insert({customer.departure, room_counter});
            rooms_needed = max(rooms_needed, room_counter);
            room_counter++;
        }
    }

    cout << rooms_needed << endl;
    for (int i = 0; i < n; ++i) {
        cout << room_assignment[i] << (i == n - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}