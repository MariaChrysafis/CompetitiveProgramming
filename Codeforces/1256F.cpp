#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
#include <array>
#include <iomanip>
 
#define ll long long
#define endl '\n'
 
using namespace std;
void print(vector<int> v){
    for(int i : v) cout << i << " ";
    cout << endl;
}
void print(vector<ll> v){
    for(ll i : v) cout << i << " ";
    cout << endl;
}
void print(vector<vector<int>> v){
    for(vector<int> vec: v) print(vec);
    cout << endl;
}
void print(vector<vector<ll>> v) {
    for (vector<ll> vec: v) print(vec);
    cout << endl;
}
string sorted(string s){
    sort(s.begin(), s.end());
    return s;
}
struct Graph{
    vector<vector<int>> adj;
    vector<int> color;
    void add_edge(int u, int v){
        adj[u].push_back(v), adj[v].push_back(u);
    }
    void dfs(int u, int col){
        //cout << u << endl;
        color[u] = col;
        for(int v: adj[u]){
            if(color[v] == -1){
                dfs(v, col);
            }
        }
    }
    int connectedComponents(){
        color.resize(adj.size());
        for(int i = 0; i < adj.size(); i++){
            color[i] = -1;
        }
        int cntr = 0;
        for(int i = 0; i < adj.size(); i++){
            if(color[i] == -1) dfs(i, cntr), cntr++;
        }
        return cntr;
    }
    void read(int n){
        adj.resize(n);
    }
};
int minNumberOfSwaps(string s1, string s2){
    Graph g;
    g.read(s1.length());
    for(int i = 0; i < s1.length(); i++){
        for(int j = 0; j < s2.length(); j++){
            if(s1[i] == s2[j]) {
                g.add_edge(i, j);
            }
        }
    }
    return s1.length() - g.connectedComponents();
}
bool solve(){
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    if(sorted(s) != sorted(t)){
        return false;
    }
    map<int,int> ocs, oct;
    for(int i = 0; i < s.length(); i++){
        if(ocs[s[i]] != 0 || oct[t[i]] != 0){
            return true;
        }
        ocs[s[i]] = i + 1;
        oct[t[i]] = i + 1;
    }
    //cout << minNumberOfSwaps(s, t) << endl;
    return (minNumberOfSwaps(s, t) % 2 == 0);
}
int main() {
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}
