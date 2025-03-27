#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, x;
    std::cin >> n >> x;

    std::vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }

    std::sort(weights.begin(), weights.end());

    //declare
    int left = 0;
    int right = n - 1;
    int gondolas = 0;

    while (left <= right) {
        //stop once pointer are equal
        if (left == right) {
            gondolas++;
            break;
        }
        
        //share a gondola if weight <= x
        if (weights[left] + weights[right] <= x) {
            left++;
            right--;
        } else {
            right--;
        }
        gondolas++;
    }

    std::cout << gondolas << std::endl;

    return 0;
}