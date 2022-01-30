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

using namespace std;
typedef int64_t ll;
vector<vector<int>> adj;
vector<int> sub;
vector<int> id;
int dfs (int curNode, int prevNode) {
    // cout << curNode << " " << prevNode << '\n';
    vector<int> children;
    for (int i: adj[curNode]) {
        if (i != prevNode) {
            dfs(i, curNode);
            children.push_back(i);
        }
    }
    if (children.empty()) {
        return (sub[curNode] = 1);
    }
    if (!id[curNode]) { //minimum
    	int ans = 0;
        for (int i: children) {
            ans += sub[i];
        }
        return (sub[curNode] = ans);
    } else { //maximum
        int ans = 1e9;
        for (int i: children) {
            ans = min(ans, sub[i]);
        }
        return (sub[curNode] = ans);
    }
}
int main() {
    int N;
    cin >> N;
    id.resize(N), adj.resize(N), sub.resize(N);
    sub.assign(N, -100);
    for (int i = 0; i < N; i++) {
        cin >> id[i];
    }
    for (int i = 0; i < N - 1; i++) {
        int u;
        cin >> u;
        u--;
        adj[u].push_back(i + 1);
        adj[i + 1].push_back(u);
    }
    int leaves = 0;
    for (int i = 1; i < N; i++) {
    	leaves += (adj[i].size() == 1);
    }
    dfs(0, -1);
    //cout << sub[0] << '\n';
    cout << leaves - sub[0] + 1;
}
