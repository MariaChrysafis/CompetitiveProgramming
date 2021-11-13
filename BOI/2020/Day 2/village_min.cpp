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
vector<vector<int>> adj;
vector<int> ans;
int tot = 0;
void dfs (int curNode, int prevNode) {
    for (int i: adj[curNode]) {
        if (i == prevNode) {
            continue;
        }
        dfs(i, curNode);
        if (ans[curNode] == -1 && ans[i] == -1) {
            ans[curNode] = i;
            ans[i] = curNode;
            tot++;
        } else if (ans[curNode] != -1 && ans[i] == -1){
            ans[i] = ans[curNode];
            ans[curNode] = i;
            tot++;
        }
    }

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    adj.resize(N), ans.assign(N, -1);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    dfs(0, -1);

    if (ans[0] == -1) {
        ans[0] = ans[adj[0].back()];
        ans[adj[0].back()] = 0;
        tot++;
    }

    cout << tot * 2 << endl;
    for (int i = 0; i < N; i++) {
        cout << ans[i] + 1 << ' ';
    }
}
