#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
struct Graph{
    vector<vector<int>> adj;
    int n;
    vector<int> solve(){
        vector<int> inDeg(n);
        for (int i = 0; i < n; i++) {
            for (int j: adj[i]) {
                inDeg[j]++;
            }
        }
        priority_queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!inDeg[i]) {
                q.push(-i);
            }
        }
        vector<int> label;
        while (!q.empty()) {
            int x = -q.top();
            q.pop();
            for (int i: adj[x]) {
                inDeg[i]--;
                if (!inDeg[i]) {
                    q.push(-i);
                }
            }
            label.push_back(x);
        }
        if (label.size() != n) {
            return {};
        }
        return label;
    }
};
vector<vector<int>> observations;
vector<int> valid(int X, int n) {
    Graph g;
    g.n = n;
    g.adj.resize(n);
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < observations[i].size() - 1; j++) {
            g.adj[observations[i][j + 1]].push_back(observations[i][j]);
        }
    }
    return g.solve();
}
int binSearch (int l, int r, int n) {
    int m = (l + r + 1)/2;
    if (l == r) {
        return l;
    }
    if (!valid(m, n).empty()) {
        return binSearch(m, r, n);
    } else {
        return binSearch(l, m -1 , n);
    }
}
int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    observations.resize(m);
    for (int i = 0; i < m; i++) {
        int sz;
        cin >> sz;
        observations[i].resize(sz);
        for (int j = 0; j < sz; j++) {
            cin >> observations[i][j];
            observations[i][j]--;
        }
        reverse(observations[i].begin(), observations[i].end());
    }
    int x = binSearch(0, m, n);
    vector<int> v = valid(x, n);
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] + 1;
        if (i != v.size() - 1) {
            cout << " ";
        }
    }
}
