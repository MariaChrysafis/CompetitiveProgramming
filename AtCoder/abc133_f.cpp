#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;
struct Edge {
    long long u, v;
    long long c, l;
};
const long long mx = 1500;
struct Unweighted_tree {
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
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
    bool onPath (int x, int u, int v) {
        if (isAncestor(v, u)) {
            swap(u, v);
        }
        if (isAncestor(u, v) || isAncestor(v, u)) {
            return (isAncestor(u, x) && isAncestor(x, v)) || (isAncestor(v, x) && isAncestor(x, u));
        }
        return onPath(x, u, leastCommonAncestor(u, v)) || onPath(x, v, leastCommonAncestor(u, v));
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
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void resz (int n) {
        adj.resize(n);
    }
    void read(){
        int n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
};
struct Tree {
    Tree (long long N) {
        depth.assign(N, 0);
    }
    map<pair<long long,long long>,long long> myMap;
    vector<long long> depth;
    void dfs (Unweighted_tree&base, long long curNode, long long prevNode) {
        depth[curNode] = depth[prevNode] + myMap[{prevNode, curNode}];
        for (long long i: base.adj[curNode]) {
            if (i != prevNode) {
                dfs(base, i, curNode);
            }
        }
    }
    void add_edge (long long u, long long v, long long w) {
        myMap[{u, v}] = myMap[{v, u}] = w;
    }
    long long findDepth (Unweighted_tree&base, long long u, long long v) {
        return depth[u] + depth[v] - 2 * depth[base.leastCommonAncestor(u, v)];
    }
    void read (Unweighted_tree base) {
        dfs(base, 0, 0);
    }
};
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N, Q;
    cin >> N >> Q;
    vector<Edge> vec(N - 1);
    map<long long,long long> cnt;
    vector<bool> heavy;
    heavy.assign(N, false);
    Tree myTree(N);
    vector<vector<long long>> mv(N);
    Unweighted_tree base;
    base.resz(N);
    for (long long i = 0; i < vec.size(); i++) {
        cin >> vec[i].u >> vec[i].v >> vec[i].c >> vec[i].l;
        vec[i].u--, vec[i].v--, vec[i].c--;
        base.add_edge(vec[i].u, vec[i].v);
        myTree.add_edge(vec[i].u, vec[i].v, vec[i].l);
        heavy[vec[i].c] = (++cnt[vec[i].c] >= mx);
        mv[vec[i].c].push_back(i);
    }
    base.read();
    myTree.read(base);
    vector<Tree> trees, trees1;
    trees.assign(N, Tree(1));
    trees1 = trees;
    for (long long i = 0; i < N; i++) {
        if (heavy[i]) {
            trees[i] = Tree(N);
            trees1[i] = Tree(N);
            for (auto& e: vec) {
                trees[i].add_edge(e.u, e.v, e.l * (e.c == i));
                trees1[i].add_edge(e.u, e.v, (e.c == i));
            }
            trees[i].read(base);
            trees1[i].read(base);
        }
    }
    while (Q--) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        x--, u--, v--;
        long long a = myTree.findDepth(base, u, v);
        if (heavy[x]) {
            a -= trees[x].findDepth(base, u, v);
            a += trees1[x].findDepth(base, u, v) * y;
            cout << a << '\n';
        } else {
            for (long long j: mv[x]) {
                if (!base.onPath(vec[j].u, u, v) || !base.onPath(vec[j].v, u, v)) {
                    continue;
                }
                a -= vec[j].l;
                a += y;
            }
            cout << a << '\n';
        }
    }

}
