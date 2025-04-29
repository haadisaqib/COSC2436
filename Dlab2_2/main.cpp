#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  vector<int> children(n);
  for (int i = 0; i < n; ++i) {
    children[i] = i + 1;
  }

  vector<int> removal_order;
  int current_index = 0;

  while (!children.empty()) {
      current_index = (current_index + k) % children.size();
      removal_order.push_back(children[current_index]);
      children.erase(children.begin() + current_index);
  }

  for (int i = 0; i < n; ++i) {
    cout << removal_order[i] << (i == n - 1 ? "" : " ");
  }
  cout << endl;

  return 0;
}