#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
struct Graph {
    vector<vector<int>> adj;
    vector<set<int>> dp;
    set<int> memoize (int curNode) {
        if (!dp[curNode].empty()) {
            return dp[curNode];
        }
        for (int i: adj[curNode]) {
            set<int> s = memoize(i);
            for (int j: s) {
                dp[curNode].insert(j + 1);
            }
        }
        return dp[curNode];
    }
    set<int> read() {
        dp.assign(adj.size(), {});
        dp.back() = {0};
        for (int i = 0; i < adj.size(); i++) {
            dp[i] = memoize(i);
        }
        return dp[0];
    }
};
int main() {
    int N1, N2, M1, M2;
    cin >> N1 >> N2 >> M1 >> M2;
    Graph g1, g2;
    g1.adj.resize(N1), g2.adj.resize(N2);
    for (int i = 0; i < M1; i++) {
        int u, v;
        cin >> u >> v;
        g1.adj[--u].push_back(--v);
    }
    for (int i = 0; i < M2; i++) {
        int u, v;
        cin >> u >> v;
        g2.adj[--u].push_back(--v);
    }
    set<int> s1 = g1.read();
    set<int> s2 = g2.read();
    set<int> s;
    for (int i: s1) {
        for (int j: s2) {
            s.insert(i + j);
        }
    }
    int q;
    cin >> q;
    while(q--) {
        int x;
        cin >> x;
        if (s.count(x)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
