#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>

using namespace std;
const int MOD = 1e9 + 9;
struct tree{
    vector<vector<int>> adj;
    vector<vector<int>> dp;
    vector<int> enter;
    vector<int> exit;
    vector<int> parent;
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
    void read (int src){
        parent.resize(adj.size());
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
        dfs(src, src);
    }
    bool onPath (int a, int b, int c) {
        if (!isAncestor(leastCommonAncestor(a, b), c)) {
            return false;
        }
        if (!isAncestor(c, a) && !isAncestor(c, b)) {
            return false;
        }
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    tree t1;
    int N, Q;
    cin >> N >> Q;
    t1.adj.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t1.adj[u].push_back(v), t1.adj[v].push_back(u);
    }
    if (N == 1) {
        while (Q--) {
            cout << 1 << '\n';
        }
        return 0;
    }
    t1.read(0);
    //cout << t1.onPath(3, 4, 2) << '\n';
    while (Q--) {
        int A, B, C;
        cin >> A >> B >> C;
        A--, B--, C--;
        if (!t1.onPath(A, B, C)) {
            cout << 0 << '\n';
            continue;
        }
        if (t1.isAncestor(C, A)) {
            swap(A, B);
        }
        int ans = 1;
        for (int i: t1.adj[C]) {
            //cout << "?" << i;
            if (!t1.onPath(A, B, i)) {
                if (i != t1.parent[C]) {
                    ans += (t1.exit[i] - t1.enter[i] + 1) / 2;
                } else {
                    ans += N - (t1.exit[C] - t1.enter[C] + 1) / 2;
                }
            }
        }
        cout << ans << '\n';
    }

}
