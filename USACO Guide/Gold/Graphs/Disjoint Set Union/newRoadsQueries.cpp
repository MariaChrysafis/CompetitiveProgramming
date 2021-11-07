#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <climits>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <iomanip>
using namespace std;
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
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
};
vector<vector<pair<int,int>>> adj;
vector<int> parent;
int dp[(int)2e5][18];
int nxt[(int)2e5][18];
vector<int> enter;
vector<int> leave;
int cntr = 1;
void dfs1 (int curNode, int prevNode) {
    parent[curNode] = prevNode;
    cntr++;
    enter[curNode] = cntr;
    for (auto p: adj[curNode]) {
        int i = p.first;
        if (i != prevNode) {
            dfs1(i, curNode);
        }
    }
    cntr++;
    leave[curNode] = cntr;
}
bool isAncestor (int u, int v) {
    return (enter[u] <= enter[v] && leave[u] >= leave[v]);
}
int leastCommonAncestor(int u, int v){
    if(isAncestor(u, v)){
        return u;
    }
    if(isAncestor(v, u)){
        return v;
    }
    for(int i = 16; i >= 0; i--){
        if(!isAncestor(nxt[u][i], v)){
            u = nxt[u][i];
        }
    }
    return nxt[u][0];
}
int rng_jump (int a, int b) {
    int myMax = 0;
    for (int i = 17; i >= 0; i--) {
        if (isAncestor(b, nxt[a][i])) {
            myMax = max(myMax, dp[a][i]);
            a = nxt[a][i];
        }
    }
    return myMax;
 
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, Q;
    cin >> N >> M >> Q;
    dsu d;
    d.n = N;
    d.fill();
    adj.resize(N);
    parent.assign(N, -1);
    enter.assign(N, -1);
    leave.assign(N, -1);
    map<pair<int,int>,int> myMap;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (d.find_head(a) != d.find_head(b)) {
            d.join(a, b);
            adj[a].push_back({b, i + 1});
            adj[b].push_back({a, i + 1});
            myMap[{a, b}] = myMap[{b, a}] = i + 1;
        }
    }
    for (int i = 0; i < N; i++) {
        if (leave[i] == -1) {
            dfs1(i, -1);
        }
    }
    for (int j = 0; j < 18; j++) {
        for (int i = 0; i < N; i++) {
            if (j == 0) {
                if (parent[i] != -1) nxt[i][j] = parent[i];
                else nxt[i][j] = i;
            } else {
                nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
            }
        }
    }
    for (int j = 0; j < 18; j++) {
        for (int i = 0; i < N; i++) {
            if (j == 0) {
                if (i == 0) dp[i][j] = 0;
                else dp[i][j] = myMap[{i, parent[i]}];
                continue;
            }
            dp[i][j] = max(dp[nxt[i][j - 1]][j - 1], dp[i][j - 1]);
        }
    }
    while(Q--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (d.find_head(a) != d.find_head(b)) {
            cout << "-1\n";
            continue;
        }
        int lca = leastCommonAncestor(a, b);
        cout << max(rng_jump(a, lca) , rng_jump(b, lca)) << '\n';
    }
}
