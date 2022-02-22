#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
class Tree {
public:
    Tree (int n) {
        adj.resize(n), vec.resize(n);
    }
    vector<vector<int>> adj;
    vector<pair<int,int>> vec;
    int lf = 1;
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    pair<int,int> unite (pair<int,int> p, pair<int,int> q) {
        if (p == (pair<int,int>){-1, -1}) return q;
        if (q == (pair<int,int>){-1, -1}) return p;
        if (p.first > q.first) {
            swap(p, q);
        }
        return make_pair(p.first, q.second);
    }
    void dfs (int curNode, int prevNode) {
        //cout << curNode << " " << prevNode << '\n';
        pair<int,int> p = {-1, -1};
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
                p = unite(p, vec[i]);
            }
        }
        if (p == make_pair(-1, -1)) {
             vec[curNode] = {lf, lf};
             lf++;
             return;
        }
        vec[curNode] = p;
    }

};
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; cin >> N;
    Tree t(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.add_edge(u, v);
    }
    t.dfs(0, -1);
    //return 0;
    for (auto& p: t.vec) {
        cout << p.first << " " << p.second << '\n';
    }
}
