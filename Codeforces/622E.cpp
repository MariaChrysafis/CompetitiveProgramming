#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef int64_t ll;

const static int MAX = 501;

vector<vector<int>> adj;
vector<int> depth;
vector<int> nodes;

void dfs (int curNode, int prevNode) {
    depth[curNode] = depth[prevNode] + 1;
    nodes.push_back(curNode);
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode);
        }
    }
}

int main() {
    int N;
    cin >> N;
    adj.resize(N), depth.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    depth[0] = 0;
    int myMax = 0;
    for (int child: adj[0]) {
        nodes.clear();
        dfs (child, 0);
        vector<int> depths;
        for (int x: nodes) {
            if (adj[x].size() == 1) {
                depths.push_back(depth[x]);
            }
        }
        sort(depths.begin(), depths.end());
        int a[depths.size()];
        a[0] = depths[0];
        for (int i = 1; i < depths.size(); i++) {
            a[i] = max(a[i - 1] + 1, depths[i]);
        }
        myMax = max(myMax, a[depths.size() - 1]);
    }
    cout << myMax;
}
