#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;
struct Tree {
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> color;
    int zero = 0;
    int one = 0;
    void dfs (int curNode, int prevNode) {
        if (curNode == 0) {
            color[curNode] = 0;
        } else {
            color[curNode] = !color[prevNode];
        }
        zero += !color[curNode];
        one += color[curNode];
        parent[curNode] = prevNode;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
            }
        }
    }
    void read() {
        parent.resize(adj.size());
        color.assign(adj.size(), -1);
        dfs(0, -1);
        if (zero < one) {
            for (int i = 0; i < adj.size(); i++) {
                color[i] = !color[i];
            }
            swap(zero, one);
        }
    }

};
void solve() {
    Tree t;
    int n;
    cin >> n;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read();
    vector<vector<int>> vec(floor(log2(n)) + 1);
    for (int i = 1; i <= n; i++) {
        vec[floor(log2(i))].push_back(i);
    }
    vector<int> labels[2];
    for (int i = 0; i < vec.size(); i++) {
        if ((t.one ^ vec[i].size()) + vec[i].size() == t.one) {
            t.one -= vec[i].size();
            for (int j: vec[i]) {
                labels[1].push_back(j);
            }
        } else {
            for (int j: vec[i]) {
                labels[0].push_back(j);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (t.color[i] == 1) {
            cout << labels[1].back() << ' ';
            labels[1].pop_back();
        } else {
            cout << labels[0].back() << ' ';
            labels[0].pop_back();
        }
    }
    cout << '\n';
    return;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    cout << '\n';
}
