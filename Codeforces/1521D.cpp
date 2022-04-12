#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;

const int MOD = 998244353;

class DisjointSetUnion {
protected:
    vector<int> parent;
    vector<int> compSize;
    int n;
    int connectedComponents;
public:
    int getConnectedComponents() const {
        return connectedComponents;
    }

public:
    void resz(int sz) {
        n = sz;
        parent.resize(sz), compSize.resize(sz);
        for (int i = 0; i < n; i++) {
            parent[i] = i, compSize[i] = 1;
        }
    }

    int find_head(int x) const {
        int cur = x;
        while (cur != parent[cur]) {
            cur = parent[cur];
        }
        return cur;
    }

    void join(int x, int y) {
        x = find_head(x);
        y = find_head(y);
        if (x == y) {
            return;
        }
        if (compSize[x] > compSize[y]) {
            swap(x, y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
        connectedComponents--;
    }

    bool comp(int x, int y) {
        return (find_head(x) == find_head(y));
    }
};

class Tree {
public:
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<set<int>> rev1, rev0;

    static bool comp1(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
        return (p1.first.first > p2.first.first);
    }

    static bool comp2(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
        return (p1.first.second > p2.first.second);
    }

    void dfs(int curNode, int prevNode) {
        dp[curNode][0] = dp[curNode][1] = 1e8;
        vector<pair<pair<int, int>, int>> val;
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs(i, curNode);
                val.push_back({{dp[i][0], dp[i][1]}, i});
            }
        }
        if (val.empty()) {
            dp[curNode] = {1, 1};
            return;
        }
        if (val.size() >= 2) {
            dp[curNode][1] = 0;
            vector<pair<int,int>> dif;
            for (int i = 0; i < val.size(); i++) {
                dp[curNode][1] += min(val[i].first.first, val[i].first.second);
                dif.push_back({val[i].first.first - min(val[i].first.first, val[i].first.second), val[i].second});
            }
            sort(dif.begin(), dif.end());
            for (int j = 0; j < min(2, (int)val.size()); j++)  {
                dp[curNode][1] += dif[j].first;
                rev1[curNode].insert(dif[j].second);
            }
            dp[curNode][1]--;
        }
        dp[curNode][0] = 0;
        vector<pair<int,int>> dif;
        for (int i = 0; i < val.size(); i++) {
            dp[curNode][0] += min(val[i].first.first, val[i].first.second);
            dif.push_back({val[i].first.first - min(val[i].first.first, val[i].first.second), val[i].second});
        }
        sort(dif.begin(), dif.end());
        rev0[curNode].insert(dif[0].second);
        dp[curNode][0] = min(dp[curNode][0] + dif[0].first, dp[curNode][0] + 1);
    }

    vector<vector<int>> bamboo;
    vector<pair<int, int>> ignored;
    DisjointSetUnion dsu;

    void dfs_bamboo(int curNode, int prevNode, bool b) {
        if (!b || dp[curNode][0] <= dp[curNode][1]) {
            int cntr = 0;
            for (int i: adj[curNode]) {
                if (i == prevNode) continue;
                if (rev0[curNode].count(i)) bamboo[i].push_back(curNode), bamboo[curNode].push_back(i), dsu.join(i, curNode), cntr++, dfs_bamboo(i, curNode, false);
                else ignored.emplace_back(i, curNode), dfs_bamboo(i, curNode, true);
            }
        } else {
            int cntr = 0;
            for (int i: adj[curNode]) {
                if (i == prevNode) continue;
                if (rev1[curNode].count(i))  bamboo[i].push_back(curNode), bamboo[curNode].push_back(i), dsu.join(i, curNode), cntr++, dfs_bamboo(i, curNode, false);
                else ignored.emplace_back(i, curNode), dfs_bamboo(i, curNode, true);
            }
        }
    }

    Tree(int n) {
        adj.resize(n), dp.assign(n, {(int) 1e8, (int) 1e8}), bamboo.resize(n);
        dsu.resz(n), rev1.resize(n), rev0.resize(n);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        Tree myTree(N);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            myTree.adj[u].push_back(v), myTree.adj[v].push_back(u);
        }
        myTree.dfs(0, 0);
        myTree.dfs_bamboo(0, 0, true);
        map<int, vector<int>> myMap;
        for (int i = 0; i < myTree.adj.size(); i++) {
            if (myTree.bamboo[i].empty()) {
                myMap[myTree.dsu.find_head(i)].push_back(i);
                myMap[myTree.dsu.find_head(i)].push_back(i);
            } else if (myTree.bamboo[i].size() == 1) {
                myMap[myTree.dsu.find_head(i)].push_back(i);
            }
        }
        vector<vector<int>> tot;
        for (auto &p: myMap) tot.push_back(p.second);
        cout << tot.size() - 1 << '\n';
        for (int i = 0; i < myTree.ignored.size(); i++) {
            cout << myTree.ignored[i].first + 1 << " " << myTree.ignored[i].second + 1 << " " << tot[i][0] + 1 << " "
                 << tot[i + 1][1] + 1 << '\n';
        }
    }
}
