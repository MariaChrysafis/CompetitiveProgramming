#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
using namespace std;
void print(vector<int> v) {
    for (int i: v) {
        cout << i << " ";
    }
    cout << endl;
}
 
void print(vector<long long> v) {
    for (long long x: v) {
        cout << x << " ";
    }
    cout << endl;
}
 
void print(vector<char> v) {
    for (char c: v) {
        cout << c;
    }
    cout << endl;
}
 
void print(vector<vector<int>> v) {
    for (vector<int> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<long long>> v) {
    for (vector<long long> vec: v) {
        print(vec);
    }
    cout << endl;
}
 
void print(vector<vector<char>> v) {
    for (vector<char> vec: v) {
        print(vec);
    }
}
 
vector<vector<int>> fill(int n, int m, int val) {
    vector<vector<int>> v;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        v[i].resize(m);
        for (int j = 0; j < m; j++) {
            v[i][j] = val;
        }
    }
    return v;
}
 
vector<int> read(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}
 
vector<long long> readll(int n) {
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    return arr;
}
int min(vector<int> v){
    int myMin = INT_MAX;
    for(int i = 0; i < v.size(); i++){
        myMin = min(myMin, v[i]);
    }
    return myMin;
}
int max(vector<int> v){
    int myMax = -INT_MAX;
    for(int i = 0; i < v.size(); i++){
        myMax = max(myMax, v[i]);
    }
    return myMax;
}
struct tree{
    vector<vector<int>> adj;
    vector<int> depth;
    vector<int> parent;
    vector<int> sub; //which subtree it belongs to
    void fill_depth(int curNode, int prevNode){
        parent[curNode] = prevNode;
        if(prevNode == -1){
            depth[curNode] = 0;
        }else{
            depth[curNode] = depth[prevNode] + 1;
        }
        for(int i: adj[curNode]){
            if(i == prevNode) continue;
            fill_depth(i, curNode);
        }
    }
    void call_depth(int root){
        depth.resize(adj.size());
        parent.resize(adj.size());
        fill_depth(root, -1);
        //print(depth);
    }
    void dfs2(int cur, int prev, int rs){
        sub[cur] = rs;
        for(int i: adj[cur]){
            if(i == prev) continue;
            dfs2(i, cur, rs);
        }
    }
    void read(int root){
        sub.resize(adj.size());
        for(int i: adj[root]){
            dfs2(i, root, i);
        }
        //print(sub);
    }
};
const int MOD = 1e9 + 7;
vector<long long> fact;
long long binPow(long long a, long long b){
    long long res = a;
    long long ans = 1;
    while(b > 0){
        if(b & 1){
            ans = (res * ans) % MOD;
        }
        res = (res * res) % MOD;
        b /= 2;
    }
    return ans;
}
 
long long inv(long long x){
    return binPow(x, MOD - 2);
}
 
long long combo(long long x, long long y){
    if(x < y) return 0;
    return (fact[x] * inv((fact[x - y] * fact[y]) % MOD)) % MOD;
}
 
int solver(vector<long long> v, int k){
    if(v.size() < k){
        return 0;
    }
    vector<vector<long long>> dp(v.size());
    for(int i = 0; i < v.size(); i++){
        dp[i].resize(v.size() + 1);
        for(int j = 0; j < dp[i].size(); j++){
            dp[i][j] = 0;
        }
        //fill((int)v.size(), (int)v.size() + 1, 0);
    }
    dp[0][0] = 1;
    dp[0][1] = v[0];
    for(int i = 1; i < v.size(); i++){
        dp[i][0] = 1;
        for(int j = 1; j <= v.size(); j++){
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * v[i]) % MOD;
        }
    }
    return dp[v.size() - 1][k];
}
 
void solve(){
    int n, k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    if(k == 1){
        cout << n << endl;
        return;
    }
    if(k == 2){
        cout << n * (n - 1)/2 << endl;
        return;
    }
    tree t;
    t.adj = adj;
    long long ans = 0;
    for(int i = 0; i < adj.size(); i++){
        t.call_depth(i);
        t.read(i);
        vector<vector<int>> cnt = fill(n, n, 0); //subtree i and depth j
        for(int j = 0; j < n; j++){
            cnt[t.depth[j]][t.sub[j]]++;
        }
        for(int j = 0; j < n; j++){
            //depth of j
            vector<long long> v;
            for(int k = 0; k < n; k++){
                if(cnt[j][k] != 0){
                    v.push_back(cnt[j][k]);
                }
            }
            ans += solver(v, k);
            ans %= MOD;
        }
    }
    cout << ans << endl;
    //cout << (ans * inv(k)) % MOD << endl;
 
}
int main(){
    fact.push_back(1);
    for(int i = 1; i < 110; i++){
        fact.push_back((fact.back() * i) % MOD);
    }
    //cout << combo(5, 2) << endl;
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
