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
const int INF = 1e9;
const int MOD = INF + 7;
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> dist(n), cnt(n);
    vector<bool> hv(n);
    for(int i = 0; i < n; i++){
        dist[i] = cnt[i] = hv[i] = 0;
    }
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    queue<int> q;
    q.push(0);
    cnt[0] = 1;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        for(int x: adj[cur]){
            if(!hv[x]){
                dist[x] = dist[cur] + 1;
                cnt[x] = cnt[cur];
                q.push(x);
                hv[x] = true;
            }else if(hv[x] && dist[x] == dist[cur] + 1){
                cnt[x] += cnt[cur];
                cnt[x] %= MOD;
            }
        }
    }
    cout << cnt[n - 1] << endl;
}
 
int main() {
    solve();
}
