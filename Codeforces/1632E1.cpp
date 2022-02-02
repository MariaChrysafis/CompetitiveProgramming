#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <string>
#include <map>
#pragma GCC optimization ("Ofast")
using namespace std;
struct tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> parent;
    vector<int> exit;
    int cntr = 1;
    int lg2;
    void dfs(int u, int prev){
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
        //is u an ancestor of v
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
    void read(){
        int n = adj.size();
        lg2 = ceil(log2(n)) + 1;
        enter.resize(n);
        exit.resize(n);
        adj.resize(n);
        dp.resize(n);
        parent.resize(n);
        for(int i = 0; i < n; i++){
            dp[i].resize(lg2 + 1);
            enter[i] = exit[i] = -1;
        }
        dfs(0, 0);
    }
    void clear () {
        adj.clear(), enter.clear(), exit.clear(), dp.clear(), parent.clear();
    }
};
class Tree {
private:
    void dfs (int curNode, int prevNode) {
        if (prevNode == -1) {
            depth[curNode] = 0;
        } else {
            depth[curNode] = depth[prevNode] + 1;
        }
        for (int i: adj[curNode]) {
            if (i == prevNode) {
                continue;
            }
            dfs (i, curNode);
        }
    }
public:
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void resz (int n) {
        adj.resize(n);
        depth.resize(n);
    }
    void read() {
        depth[0] = 0;
        dfs (0, -1);
    }
    void clear () {
        depth.clear(), adj.clear();
    }
    vector<int> depth;
    vector<vector<int>> adj;
};
Tree myTree;
tree t;

int find_dist (int u, int v) {
    return (myTree.depth[u] + myTree.depth[v] - 2 * myTree.depth[t.leastCommonAncestor(u, v)]);
}

bool isValid (int d, int w) {
    int ind = 0;
    for (int i = 0; i < myTree.adj.size(); i++) {
        if (myTree.depth[i] > myTree.depth[ind]) {
            ind = i;
        }
    }
    if (myTree.depth[ind] <= d) {
        return true;
    }
    int x = ind;
    while (myTree.depth[ind] - myTree.depth[x] + w < d) {
        x = t.parent[x];
    }
    assert(x >= 0);
    for (int i = 0; i < myTree.adj.size(); i++) {
        if (min(find_dist(i, x) + w, myTree.depth[i]) > d) {
            return false;
        }
    }
    return true;
}
void solve () {
    int N;
    cin >> N;
    myTree.clear(), t.clear();
    myTree.resz(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v; u--, v--;
        myTree.add_edge(u, v);
    }
    t.adj = myTree.adj;
    t.read();
    myTree.read();
    for (int w = 1; w <= N; w++) {
        //we can add something of weight w
        int l = 0;
        int r = N;
        while (l != r) {
            int m = (l + r)/2;
            if (isValid(m, w)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        cout << l << ' ';
    }
    cout << '\n';
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
}
