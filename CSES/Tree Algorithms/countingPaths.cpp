#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#define ll long long
using namespace std;
const int N = 90;
struct tree{
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
    void read (){
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
tree t;
vector<int> val, sub;
int dfs (int curNode, int prevNode) {
    sub[curNode] = val[curNode];
    for (int i: t.adj[curNode]) {
        if (i != prevNode) {
            sub[curNode] += dfs(i, curNode);
        }
    }
    return sub[curNode];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //cout << corrupted("<()<>>");
    int n, m;
    cin >> n >> m;
    t.adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        t.adj[u].push_back(v), t.adj[v].push_back(u);
    }
    t.read();
    val.assign(n, 0), sub = val; vector<int> add = val;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        val[u]++; val[v]++; val[t.leastCommonAncestor(u, v)] -= 2;
        add[t.leastCommonAncestor(u, v)]++;
    }
    dfs(0, -1);
    for (int i = 0; i < sub.size(); i++) {
        cout << sub[i] + add[i] << ' ';
    }
 
}
