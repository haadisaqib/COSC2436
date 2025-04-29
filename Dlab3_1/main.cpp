#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (auto &row : grid) cin >> row;

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};

    int rooms = 0;
    vector<vector<bool>> vis(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '.' && !vis[i][j]) {
                ++rooms;
                // iterative DFS
                stack<pair<int,int>> st;
                st.push({i, j});
                vis[i][j] = true;

                while (!st.empty()) {
                    auto [x, y] = st.top();
                    st.pop();
                    for (int k = 0; k < 4; ++k) {
                        int nx = x + dx[k], ny = y + dy[k];
                        if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                            grid[nx][ny] == '.' && !vis[nx][ny]) {
                            vis[nx][ny] = true;
                            st.push({nx, ny});
                        }
                    }
                }
            }
        }
    }

    cout << rooms << '\n';
    return 0;
}
