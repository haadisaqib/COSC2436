#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main() {
  int n;
  cin >> n;
 
  vector<pair<int, int>> ranges(n);
  for (int i = 0; i < n; ++i) {
    cin >> ranges[i].first >> ranges[i].second;
  }
 
  // Contains Count
  vector<int> contains_count(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && ranges[i].first <= ranges[j].first && ranges[j].second <= ranges[i].second) {
        contains_count[i]++;
      }
    }
  }
 
  // Is Contained By Count
  vector<int> is_contained_by_count(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i != j && ranges[j].first <= ranges[i].first && ranges[i].second <= ranges[j].second) {
        is_contained_by_count[i]++;
      }
    }
  }
 
  // Output Contains Count
  for (int i = 0; i < n; ++i) {
    cout << contains_count[i] << (i == n - 1 ? "" : " ");
  }
  cout << endl;
 
  // Output Is Contained By Count
  for (int i = 0; i < n; ++i) {
    cout << is_contained_by_count[i] << (i == n - 1 ? "" : " ");
  }
  cout << endl;
 
  return 0;
}