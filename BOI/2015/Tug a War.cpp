#include <bits/stdc++.h>
using namespace std;
vector<multiset<pair<int,int> > > adj;
vector<bool> hasVisited;
int ans = 0;
void dfs (int curNode, int prevNode) {
    if (hasVisited[curNode]) {
        return;
    }
    hasVisited[curNode] = true;
    for (pair<int,int> p: adj[curNode]) {
        if (p.first != prevNode) {
            ans += p.second;
            dfs (p.first, curNode);
        }
    }
}
int c = 0;
void apply () {
    queue<int> q;
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i].size() == 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        pair<int,int> p = *adj[x].begin();
        c += p.second;
        adj[x].clear();
        adj[p.first].erase(adj[p.first].find(make_pair(x, -p.second)));
        if (adj[p.first].size() == 1) {
            q.push(p.first);
        }
        if (adj[p.first].empty()) {
            cout << "NO\n";
            exit(0);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    adj.resize(2 * n);
    hasVisited.assign(2 * n, false);
    map<pair<int,int>,vector<int> > myMap;
    for (int i = 0; i < 2 * n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        v += n;
        myMap[make_pair(u, v)].push_back(w);
        adj[u].insert(make_pair(v, w));
        adj[v].insert(make_pair(u, -w));
    }
    for (int i = 0; i < 2 * n; i++) {
        if (adj[i].empty()) {
            cout << "NO\n";
            exit(0);
        }
    }
    apply();
    vector<int> tot;
    for (int i = 0; i < n; i++) {
        if (!hasVisited[i] && !adj[i].empty()) {
            ans = 0;
            dfs (i, (*adj[i].rbegin()).first);
            tot.push_back(abs(ans));
        }
    }
    for (auto& p: myMap) {
        if (p.second.size() <= 1) {
            continue;
        }
        int a = 0;
        for (int j = 0; j < p.second.size(); j++) {
            if (j % 2) a += p.second[j];
            else a -= p.second[j];
        }
        tot.push_back(abs(a));
    }
    bitset<600000> bs;
    bs.set(c + 300000);
    for (int j: tot) {
        bs = (bs >> j) | (bs << j);
    }
    for (int i = -k; i <= k; i++) {
        if (bs[300000 + i]) {
            cout << "YES\n";
            return 0;
        }
    }
    cout << "NO\n";
}
