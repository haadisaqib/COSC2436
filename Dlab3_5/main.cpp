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

    vector<int> team(n + 1, 0);          // 0 = unvisited, 1 or 2 = team
    queue<int> q;

    for (int s = 1; s <= n; ++s) {
        if (team[s]) continue;           // already colored in previous BFS
        team[s] = 1;
        q.push(s);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (team[v] == 0) {      // unvisited
                    team[v] = 3 - team[u];   // opposite team (1↔2)
                    q.push(v);
                } else if (team[v] == team[u]) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) cout << team[i] << (i == n ? '\n' : ' ');
    return 0;
}
