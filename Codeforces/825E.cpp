#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> inDeg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[v].push_back(u);
        inDeg[u]++;
    }
    priority_queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) {
            q.push(i);
        }
    }
    int label[n];
    int cntr = -1;
    while (!q.empty()) {
        cntr++;
        int x = q.top();
        q.pop();
        for (int i: adj[x]) {
            inDeg[i]--;
            if (inDeg[i] == 0) {
                q.push(i);
            }
        }
        label[x] = cntr;
    }
    for (int i: label) {
        cout << n - i << ' ';
    }
    cout << '\n';
}
int main() {
    solve();
}
