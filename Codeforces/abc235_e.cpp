#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

struct dsu{
    vector<int> parent;
    vector<int> compSize;
    int n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    int find_head(int x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(int x, int y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};

struct Tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter, parent, exit, depth;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
        if (u == 0) depth[u] = 0;
        else depth[u] = depth[prev] + 1;
        parent[u] = prev;
        cntr++;
        enter[u] = cntr;
        dp[u][0] = prev;
        for(int i = 1; i <= lg2; i++){
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for(int v: adj[u]){
            if(v != prev){
                dfs(v, u);
            }
        }
        cntr++;
        exit[u] = cntr;
    }
    bool isAncestor(int u, int v){
        return (enter[u] <= enter[v] && exit[u] >= exit[v]);
    }
    int leastCommonAncestor(int u, int v){
        if(isAncestor(u, v)){
            return u;
        }
        if(isAncestor(v, u)){
            return v;
        }
        for(int i = lg2; i >= 0; i--){
            if(!isAncestor(dp[u][i], v)){
                u = dp[u][i];
            }
        }
        return dp[u][0];
    }
    void read (){
        int n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        parent.resize(n), depth.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};


struct TreeMin {
    //find the minimum value on the path between two nodes
    vector<vector<int>> adj, dp, nxt;
    map<pair<int,int>,int> val;
    Tree t;

    int get_up (int u, int len) {
        if (len == 0) {
            return 0;
        }
        int lg2 = log2(len);
        int x1 = dp[u][lg2];
        int x2 = get_up(nxt[u][lg2], len - (1 << lg2));
        //cout << x1 << " " << x2 << " " << dp[1][0] << '\n';
        return max(x1, x2);
    }

    int get_to (int u, int v) {
        if (u == v) {
            return 0;
        }
        assert(t.depth[u] >= t.depth[v]);
        return get_up(u, t.depth[u] - t.depth[v]);
    }

    int query (int u, int v) {
        return max(get_to(u, t.leastCommonAncestor(u, v)), get_to(v, t.leastCommonAncestor(u, v)));
    }

    void fill () {
        dp.resize(t.adj.size()), nxt.resize(t.adj.size());
        for (int i = 0; i < dp.size(); i++) {
            dp[i].resize(32);
            nxt[i].resize(32);
        }
        for (int j = 0; j < dp[0].size(); j++) {
            for (int i = 0; i < dp.size(); i++) {
                if (j == 0) {
                    nxt[i][j] = t.parent[i];
                    if (nxt[i][j] == -1) nxt[i][j] = i;
                } else {
                    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
                }
            }
        }
        for (int j = 0; j < dp[0].size(); j++) {
            for (int i = 0; i < dp.size(); i++) {
                if (j == 0) {
                    dp[i][j] = val[{i, t.parent[i]}];
                    if (i == 0) dp[i][j] = 0;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[nxt[i][j - 1]][j - 1]);
                }
            }
        }
    }

    void read () {
        t.adj = adj;
        t.read();
        fill();
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, Q;
    cin >> N >> M >> Q;
    dsu ds;
    ds.n = N;
    ds.fill();
    vector<pair<int,pair<int,int>>> vec(M);
    for (int i = 0; i < M; i++) {
        cin >> vec[i].second.first >> vec[i].second.second >> vec[i].first;
        vec[i].second.first--, vec[i].second.second--;
    }
    sort(vec.begin(), vec.end());
    TreeMin t;
    t.adj.resize(N);
    for (auto& p: vec) {
        if (ds.comp(p.second.first, p.second.second)) {
            continue;
        }
        ds.join(p.second.first, p.second.second);
        t.val[{p.second.first, p.second.second}] = t.val[{p.second.second, p.second.first}] = p.first;
        t.adj[p.second.first].push_back(p.second.second);
        t.adj[p.second.second].push_back(p.second.first);
        //cout << p.second.first << "->" << p.second.second << ": " << p.first << '\n';
    }
    t.read();
    while (Q--) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        if (u == v) {
            cout << "No\n";
            continue;
        }
        if (t.query(u, v) < w) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
        }
    }
}
