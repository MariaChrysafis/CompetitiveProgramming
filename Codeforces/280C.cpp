#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

vector<vector<int>> adj;
vector<int> rootDistance;

void dfs (int curNode, int prevNode, int dist) {
    rootDistance[curNode] = dist;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode, dist + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    adj.resize(N), rootDistance.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1, 1);
    double ans = 0;
    for (int i = 0; i < N; i++) {
        ans += 1/(double)rootDistance[i];
    }
    cout << setprecision(30) << ans;
}
