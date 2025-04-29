#include <bits/stdc++.h>
using namespace std;

struct Node {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (auto &row : grid) cin >> row;

    // Locate start (A) and target (B)
    Node start{-1,-1}, target{-1,-1};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'A') start = {i, j};
            else if (grid[i][j] == 'B') target = {i, j};
        }

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    const char dirChar[4] = {'D', 'U', 'R', 'L'};

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<char>> prevDir(n, vector<char>(m, 0));
    vector<vector<Node>> parent(n, vector<Node>(m, {-1, -1}));

    queue<Node> q;
    q.push(start);
    vis[start.x][start.y] = true;

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();
        if (cur.x == target.x && cur.y == target.y) break;

        for (int k = 0; k < 4; ++k) {
            int nx = cur.x + dx[k], ny = cur.y + dy[k];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (vis[nx][ny] || grid[nx][ny] == '#') continue;
            vis[nx][ny] = true;
            prevDir[nx][ny] = dirChar[k];          // how we reached (nx,ny)
            parent[nx][ny] = cur;                  // from which cell
            q.push({nx, ny});
        }
    }

    if (!vis[target.x][target.y]) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruct path
    string path;
    for (Node cur = target; !(cur.x == start.x && cur.y == start.y); ) {
        char d = prevDir[cur.x][cur.y];
        path.push_back(d);
        cur = parent[cur.x][cur.y];
    }
    reverse(path.begin(), path.end());

    cout << "YES\n" << path.size() << '\n' << path << '\n';
    return 0;
}
