#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>

using namespace std;
class Graph {
    vector<vector<int>> adj;
    vector<bool> hasVisited;
    int cntr = 0;
public:
    void add_edge (int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs (int curNode) {
        if (hasVisited[curNode]) {
            return;
        }
        hasVisited[curNode] = true;
        cntr++;
        for (int i: adj[curNode]) {
            dfs (i);
        }
    }
    vector<int64_t> cycles () {
        hasVisited.assign(adj.size(), false);
        vector<int64_t> v;
        for (int i = 0; i < hasVisited.size(); i++) {
            if (!hasVisited[i]) {
                dfs (i);
                v.push_back(cntr);
                cntr = 0;
            }
        }
        return v;
    }
    Graph (int n) {
        adj.resize(n);
    }
};
const int MAXN = 2e5 + 1;
int mob[MAXN];
int divisors[MAXN];
void solve () {
    int64_t n;
    cin >> n;
    vector<int64_t> a(n), b(n);
    Graph g1(n), g2(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g1.add_edge(a[i] - 1, i);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        g2.add_edge(b[i] - 1, i);
    }
    vector<int64_t> v1 = g1.cycles();
    vector<int64_t> v2 = g2.cycles();
    vector<int64_t> d1(n + 1), d2(n + 1);
    for (int i: v1) {
        for (int j = 1; j <= sqrt(i); j++) {
            if (i % j == 0) {
                d1[j]++;
                d1[i/j]++;
            }
            if (j * j == i) {
                d1[j]--;
            }
        }
    }
    for (int64_t i: v2) {
        for (int64_t j = 1; j <= sqrt(i); j++) {
            if (i % j == 0) {
                d2[j]++;
                d2[i/j]++;
            }
            if (j * j == i) {
                d2[j]--;
            }
        }
    }
    int64_t ans = 0;
    for (int i = 1; i <= n; i++) {
        if (d1[i] == 0 || d2[i] == 0) {
            continue;
        }
        int64_t cntr = 0;
        for (int j = i; j <= n; j += i) {
            if (d1[j] == 0 || d2[j] == 0) {
                continue;
            }
            cntr += mob[j/i] * d1[j] * d2[j];
        }
        ans += cntr * i;
    }
    cout << n * n - ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mob[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        if (mob[i] == false) {
            for (int j = i; j < MAXN; j += i) {
                mob[j]++;
            }
        }
    }
    for (int i = 2; i < MAXN; i++) {
        mob[i] = pow(-1, mob[i] % 2);
    }
    for (int j = 2; j * j < MAXN; j++) {
        for (int k = 1; j * j * k < MAXN; k++) {
            mob[j * j * k] = 0;
        }
    }
    divisors[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        divisors[i]++;
        for (int j = i; j < MAXN; j += i) {
            divisors[j]++;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
