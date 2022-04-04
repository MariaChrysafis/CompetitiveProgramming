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
#define ll long long
#include <map>
 
using namespace std;
class Tree {
protected:
    vector<vector<int>> adj;
    vector<int> sub;
public:
    Tree (int n) {
        adj.resize(n), sub.resize(n);
    }
    void dfs1 (int curNode, int prevNode) {
        sub[curNode] = 1;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs1(i, curNode), sub[curNode] += sub[i];
            }
        }
    }
    int get_centroid (int curNode, int prevNode) {
        for (int i: adj[curNode]) {
            if (i != prevNode && sub[i] > (int)adj.size()/2) {
                return get_centroid(i, curNode);
            }
        }
        return curNode;
    }
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void read () {
        dfs1(0, 0);
        cout << get_centroid(0, -1) + 1 << '\n';
    }
};
int main() {
    int N;
    cin >> N;
    Tree myTree(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.read();
 
}
