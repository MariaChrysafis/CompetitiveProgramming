#include <bits/stdc++.h>
using namespace std;
class Tree {
    vector<vector<int> > adj;
    vector< multiset<int> > depths;
    int k;
public:
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void merge (multiset<int>& ms1, multiset<int>& ms2, int k) {
        if (ms1.size() > ms2.size()) {
            swap(ms1, ms2);
        }
        for (int i: ms1) {
            auto it = ms2.upper_bound(k - i);
            if (it == ms2.begin()) {
                ms2.insert(i);
            } else {
                int x = *(--it);
                ms2.erase(ms2.find(x));
                ms2.insert(max(x, i));
            }
        }
    }
    void dfs (int curNode, int prevNode, int d) {
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode, d + 1);
                merge(depths[i], depths[curNode], k + 2 * d);
                depths[i].clear();
            }
        }
        if (depths[curNode].empty()) {
            depths[curNode].insert(d);
        }
    }
    Tree (int n, int k) {
        this->k = k;
        adj.resize(n);
        depths.resize(n);
    }
    void read() {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i].size() != 1) {
                dfs(i, i, 0);
                cout << depths[i].size();
                exit(0);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    Tree myTree(n, k);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.read();
}
