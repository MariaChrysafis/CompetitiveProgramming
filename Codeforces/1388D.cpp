#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>
 
using namespace std;
void print(vector<long long> v){
    for(long long i: v) cout << i + 1 << " ";
}
vector<bool> hasVisited;
vector<vector<long long>> adj;
vector<long long> order[2];
vector<long long> a, b;
long long ans = 0;
void dfs(long long u){
    hasVisited[u] = true;
    for(long long x: adj[u]){
        if(!hasVisited[x]){
            dfs(x);
        }
    }
    ans += a[u];
    if(b[u] != -1 && a[u] > 0){
        a[b[u]] += a[u];
    }
    if(a[u] > 0){
        order[0].push_back(u);
    }else{
        order[1].push_back(u);
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    a.resize(n), b.resize(n), hasVisited.resize(n), adj.resize(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
        if(b[i] != -1) {
            b[i]--, adj[b[i]].push_back(i);
        }
        hasVisited[i] = false;
    }
    for(int i = 0; i < n; i++){
        if(!hasVisited[i]){
            dfs(i);
        }
    }
    reverse(order[1].begin(), order[1].end());
    cout << ans << endl;
    print(order[0]);
    print(order[1]);
 
}
