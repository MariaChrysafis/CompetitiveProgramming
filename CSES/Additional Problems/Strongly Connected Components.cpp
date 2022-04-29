#include <bits/stdc++.h>
using namespace std;
 
vector<vector<int> > adj, new_adj;
vector<int> depth;
set<pair<int,int> > edges;
vector<int> sub;
vector<pair<int,int> > ans;
vector<bool> hasVisited;
vector<int> parent;
 
void dfs (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    depth[curNode] = depth[prevNode] + 1;
    hasVisited[curNode] = true;
    for (int i: adj[curNode]) {
        if (!hasVisited[i]) {
            new_adj[i].push_back(curNode), new_adj[curNode].push_back(i), edges.insert(make_pair(i, curNode)), ans.push_back(make_pair(curNode, i));
            dfs (i, curNode);
        }
    }
}
 
void fill (int curNode, int prevNode)  {
    for (int i: new_adj[curNode]) {
        if (i != prevNode) {
            fill (i, curNode);
            sub[curNode] += sub[i];
        }
    }
}
 
int main() {
    int N, M;
    cin >> N >> M;
    adj.resize(N), depth.assign(N, false), sub.assign(N, 0), new_adj.resize(N), hasVisited.assign(N, false), parent.resize(N);
    while (M--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs (0, 0);
    for (int i = 0; i < adj.size(); i++) {
        if (!hasVisited[i]) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
        for (int j: adj[i]) {
            if (depth[i] > depth[j] && !edges.count(make_pair(i, j)) && !edges.count(make_pair(j, i))) {
                sub[i]++;
                if (j != 0) {
                    sub[j]--;
                }
            }
        }
    }
    fill(0, 0);
    for (int i = 0; i < adj.size(); i++) {
        if (sub[i] == 0) {
            cout << "IMPOSSIBLE\n";
            exit(0);
        }
    }
    for (int i = 0; i < adj.size(); i++) {
        for (int j: adj[i]) {
            if (edges.count(make_pair(i, j)) || edges.count(make_pair(j, i))) {
                continue;
            }
            assert(depth[i] != depth[j]);
            if (depth[i] > depth[j]) {
                edges.insert(make_pair(i, j));
                ans.push_back(make_pair(i, j));
            }
        }
    }
    for (auto& p: ans) {
        cout << p.first + 1 << " " << p.second + 1 << '\n';
    }
}
