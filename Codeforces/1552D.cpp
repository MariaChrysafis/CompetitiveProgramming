#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
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
bool compare(vector<int> v1, vector<int> v2){
    int cntr = 0;
    for(int i = 0; i < 5; i++){
        if(v1[i] < v2[i]){
            cntr++;
        }
    }
    return (cntr >= 3);
}
bool comp(vector<int> v1, vector<int> v2){
    vector<int> v11 = v1; sort(v11.begin(), v11.end());
    vector<int> v21 = v2; sort(v21.begin(), v21.end());
    int x = v11[0] + v11[1] + v11[2];
    int y = v21[0] + v21[1] + v21[2];
    return (x <= y);
}
 
int distance(int i, int j, int n){
    return min(abs(i - j), 2 * n - abs(i - j));
}
 
bool intersects(pair<int,int> p1, pair<int,int> p2, int n){
    if(p1.first == p2.first) return false;
    if(p1.first > p1.second) swap(p1.first , p1.second);
    if(p2.first < p2.second) swap(p2.first, p2.second);
    int dist1 = distance(p1.first, p1.second, n)
                + distance(p1.second, p2.first, n)
                + distance(p2.first, p2.second, n)
                + distance(p2.second, p1.first, n);
    if(dist1 != 2 * n){
        return true;
    }
    if(p1.first < p1.second) swap(p1.first , p1.second);
    if(p2.first > p2.second) swap(p2.first, p2.second);
    dist1 = distance(p1.first, p1.second, n)
            + distance(p1.second, p2.first, n)
            + distance(p2.first, p2.second, n)
            + distance(p2.second, p1.first, n);
    if(dist1 != 2 * n){
        return true;
    }
    return false;
}
vector<string> tot;
void rec(string s, int des){
    if(s.length() == des){
        tot.push_back(s);
        return;
    }
    rec(s + '1', des), rec(s + '0', des), rec(s + '2', des);
}
bool solve() {
    tot.clear();
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    rec("", n);
    for(string s: tot){
        int cntr = 0;
        bool fine = false;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '0') cntr += v[i], fine = true;
            else if(s[i] == '1') cntr -= v[i], fine = true;
        }
        if(cntr == 0 && fine){
            return true;
        }
    }
    return false;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        //cout << b << endl;
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
