#include <bits/stdc++.h>
using namespace std;
void rec (set<int>& color, vector<int>& sub, vector<vector<int> > &adj, int curNode, int prevNode) {
    sub[curNode] = (bool)color.count(curNode);
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            rec (color, sub, adj, i, curNode);
            sub[curNode] += sub[i];
        }
    }
}
int cntr = 0;
int lst = 0;
void dfs (vector<int>& sub_y, vector<int>& sub, vector<vector<int> >& adj, int curNode, int prevNode) {
    //cout << curNode + 1 << '\n';
    lst = curNode;
    for (int i: adj[curNode]) {
        if (i != prevNode && !sub_y[i] && sub[i]) {
            dfs (sub_y, sub, adj, i, curNode);
            cntr += 2;
        }
    }
    for (int i: adj[curNode]) {
        if (i != prevNode && sub_y[i]) {
            dfs (sub_y, sub, adj, i, curNode);
            cntr ++;
        }
    }
}
int distance (vector<vector<int> > & adj, int u, int v) {
    vector<bool> hasVisited;
    hasVisited.assign(adj.size(), false);
    queue<pair<int,int> > q;
    q.push(make_pair(u, 0));
    hasVisited[u] = true;
    while (!q.empty()) {
        pair<int,int> p = q.front();
        q.pop();
        if (p.first == v) {
            return p.second;
        }
        for (int i: adj[p.first]) {
            if (!hasVisited[i]) {
                q.push(make_pair(i, p.second + 1));
                hasVisited[i] = true;
            }
        }
    }

}
void solve() {
    cntr = 0;
    int n, k;
    cin >> n >> k;
    int x, y; 
    cin >> x >> y;
    x--,  y--;
    vector<int> a(k), sub(n), sub_y(n); set<int> color;
    for (int i = 0; i < k; i++) {
        cin >> a[i];
        a[i]--;
        color.insert(a[i]);
    }
    vector<vector<int> > adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    rec(color, sub, adj, x, x);
    set<int> dum; dum.insert(y);
    rec(dum, sub_y, adj, x, x);
    dfs(sub_y, sub, adj, x, x);
    cout << cntr << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
