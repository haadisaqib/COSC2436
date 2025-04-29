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

    vector<int> rep;                    // one representative per component
    vector<char> vis(n + 1, 0);
    stack<int> st;

    for (int v = 1; v <= n; ++v) {
        if (vis[v]) continue;
        rep.push_back(v);               // first node we meet = component root

        st.push(v);
        vis[v] = 1;
        while (!st.empty()) {           // iterative DFS to mark component
            int cur = st.top();
            st.pop();
            for (int nxt : adj[cur]) {
                if (!vis[nxt]) {
                    vis[nxt] = 1;
                    st.push(nxt);
                }
            }
        }
    }

    int k = (int)rep.size() - 1;        // roads needed = components − 1
    cout << k << '\n';
    for (int i = 0; i < k; ++i)
        cout << rep[i] << ' ' << rep[i + 1] << '\n';
    return 0;
}
