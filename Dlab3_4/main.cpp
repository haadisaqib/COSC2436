#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<int>> adj(n + 1);
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> parent(n + 1, -1);
    queue<int> q;
    q.push(1);
    parent[1] = 0;                 // mark as visited

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == n) break;
        for (int v : adj[u]) {
            if (parent[v] == -1) {
                parent[v] = u;
                q.push(v);
            }
        }
    }

    if (parent[n] == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    for (int cur = n; cur; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (int node : path) cout << node << ' ';
    cout << '\n';
    return 0;
}
