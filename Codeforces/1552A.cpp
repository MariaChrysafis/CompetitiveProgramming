#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
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
 
void solve(){
    int n;
    cin >> n;
    vector<char> s;
    string str;
    cin >> str;
    //cout << str <<
    string str1 = str;
    sort(str1.begin(), str1.end());
    for(int i = 0; i < n; i++){
        if(str1[i] != str[i]){
            s.push_back(str1[i]);
        }
    }
    cout << s.size() << endl;
}
 
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
