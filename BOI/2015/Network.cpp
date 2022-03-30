#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
 
using namespace std;
vector<vector<int>> adj;
vector<int> nodes;
void dfs (int curNode, int prevNode) {
    if (adj[curNode].size() == 1) {
        nodes.push_back(curNode);
    }
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs (i, curNode);
        }
    }
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs (0, 0);
    cout << (nodes.size() + 1)/2 << '\n';
    for (int i = 0; i < (nodes.size() + 1)/2; i++) {
        cout << nodes[i] + 1 << " " << nodes[i + nodes.size()/2] + 1 << '\n';
    }
}
