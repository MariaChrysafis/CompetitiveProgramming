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

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#pragma GCC optimization ("Ofast")
using namespace std;
class Tree {
public:
    vector<vector<int>> adj;
    vector<int> arr, ip;
    vector<int> depths;
    vector<int> st, en, parent, max_sub, max_sub_exc;
    vector<vector<int>> dp;
    vector<vector<int64_t>> dp_max;
    int cntr = 0;
    int64_t C, D;
    Tree (int64_t n, int64_t C, int64_t D, vector<int> arr) {
        this->C = C, this->D = D;
        adj.resize(n);
        this->arr = arr;
        ip.resize(arr.size()), st.resize(arr.size()), en.resize(arr.size()), parent.resize(arr.size()), dp.resize(arr.size()), max_sub.resize(arr.size()), dp_max.resize(arr.size());
        max_sub_exc.assign(arr.size(), -1);
        for (int i = 0; i < arr.size(); i++) {
            dp[i].resize(32);
            dp_max[i].resize(32);
            ip[arr[i]] = i;
        }
    }

    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }

    void dfs (int curNode, int prevNode) {
        parent[curNode] = prevNode;
        st[curNode] = cntr++;
        max_sub[curNode] = arr[curNode];
        for (int i: adj[curNode]) {
            if (i != prevNode) {
                dfs (i, curNode);
                max_sub[curNode] = max(max_sub[curNode], max_sub[i]);
            }
        }
        en[curNode] = cntr++;
    }

    bool isAncestor (int u, int v) {
        //is u an ancestor of v?
        return (st[u] <= st[v] && en[u] >= en[v]);
    }

    int leastCommonAncestor (int u, int v) {
        //cout << "GET " << u << " " << v << '\n';
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = 31; i >= 0; i--) {
            if (!isAncestor(dp[u][i], v)) {
                u = dp[u][i];
            }
        }
        //cout << u << " " << v << '\n';
        //assert(u == v);
        return dp[u][0];
    }

    int L = -1;
    int R = -1;

    int64_t get_max (int left, int right) {
        if (left == right) {
            return arr[left];
        }
        int lg2 = log2(depths[left] - depths[right]);
        return max(get_max(dp[left][lg2], right), dp_max[left][lg2]);
    }

    void fill() {
        depths.assign(adj.size(), -1);
        queue<pair<int,int>> q;
        q.push(make_pair(0, 0));
        while (!q.empty()) {
            pair<int,int> p = q.front();
            q.pop();
            if (depths[p.first] != -1) {
                continue;
            }
            depths[p.first] = p.second;
            for (int i: adj[p.first]) {
                q.push({i, p.second + 1});
            }
        }
        dfs(0, -1);
        for (int i = 0; i < adj.size(); i++) {
            dp[i][0] = max(parent[i], 0);
            dp_max[i][0] = max(arr[dp[i][0]], arr[i]);
        }
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < adj.size(); i++) {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
                dp_max[i][j] = max(dp_max[i][j - 1], dp_max[dp[i][j - 1]][j - 1]);
            }
        }
    }

    int rec (int curNode) {
        if (max_sub_exc[curNode] != -1) {
            return max_sub_exc[curNode];
        }
        max_sub_exc[curNode] = 0;
        if (parent[curNode] == -1) {
            return max_sub_exc[curNode];
        }
        max_sub_exc[curNode] = max(rec(parent[curNode]), arr[parent[curNode]]);
        for (int i: adj[parent[curNode]]) {
            if (i == curNode || i == parent[parent[curNode]]) {
                continue;
            }
            max_sub_exc[curNode] = max(max_sub_exc[curNode], max_sub[i]);
        }
        return max_sub_exc[curNode];
    }

    int64_t get_cost () {
        if (!isAncestor(L, R) && !isAncestor(R, L)) {
            int lr = max(max_sub[L], max_sub[R]);
            lr = max(lr, (int)get_max(L, leastCommonAncestor(L, R)));
            lr = max(lr, (int)get_max(R, leastCommonAncestor(L, R)));
            return lr;
        }
        if (isAncestor(L, R)) {
            swap(L, R);
        }
        int myMax = get_max(L, R);
        myMax = max(myMax, max_sub[L]);
        for (int i: adj[R]) {
            if (isAncestor(i, L)) continue;
            myMax = max(myMax, max_sub[i]);
        }
        myMax = max(myMax, max(max(arr[L], arr[R]), rec(R)));
        return myMax;
    }

    bool contains (int left, int right, int myNode) {
        if (isAncestor(right, left)) {
            swap(left, right);
        }
        if (isAncestor(left, right)) {
            return (isAncestor(myNode, right) && isAncestor(left, myNode));
        }
        int lca = leastCommonAncestor(left, right);
        if (isAncestor(myNode, left) && isAncestor(lca, myNode)) {
            return true;
        }
        if (isAncestor(myNode, right) && isAncestor(lca, myNode)) {
            return true;
        }
        return false;
    }

    void compute () {
        L = ip[0];
        R = ip[0];
        int64_t ans = 0;
        bool broken = false;
        for (long long i = 1; i < (int)adj.size(); i++) {
            ans = max(get_cost() * D + i * C, ans);
            if (contains(ip[i], L, R)) {
                R = ip[i];
                continue;
            }
            if (contains(ip[i], R, L)) {
                L = ip[i];
                continue;
            }
            if (contains(L, R, ip[i])) {
                continue;
            }
            cout << ans;
            exit(0);
        }
        cout << (int64_t)adj.size() * D - D + (int64_t)(adj.size()) * C << '\n';
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, C, D;
    cin >> N >> C >> D;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    Tree myTree(N, C, D, arr);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v; u--, v--;
        myTree.add_edge(u, v);
    }
    myTree.fill();
    myTree.compute();
}
