#include <bits/stdc++.h>
#define ALL(x) (x).begin(), (x).end()
#define sz(s) (int)(s).size()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
int t, tc, n, m, h[100500], tin[100500], color[100500];
vector<int> s, g[100500];
void dfs(int v) {
    h[v] = tin[v] = ++t;
    s.push_back(v);
    for (int u: g[v]) {
        if (!tin[u]) {
            dfs(u);
            h[v] = min(h[v], h[u]);
        }
        else if (!color[u]) h[v] = min(h[v], h[u]);
    }
    if (h[v] == tin[v])
        for (++tc; !color[v]; s.pop_back())
            color[s.back()] = tc;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u - 1].push_back(v - 1);
    }
    for (int v = 0; v < n; v++)
        if (!tin[v]) dfs(v);
    cout << tc << endl;
    for (int i = 0; i < n; i++) {
        cout << tc - color[i] + 1 << " ";
    }
}
