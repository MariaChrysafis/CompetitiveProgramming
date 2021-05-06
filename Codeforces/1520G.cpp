#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#define coord pair<ll,ll>
#define ll long long
#define x first
#define y second
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast")//Comment optimisations for interactive problems (use endl)
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
using namespace std;
void prll(vector<vector<ll>> v){
    for(ll i = 0; i < v.size(); i++){
        for(ll j: v[i]){
            cout << j << " ";
        }
        cout << endl;
    }
}
ll min(ll a, ll b){
    if(a < b) return a;
    return b;
}
ll MA(ll a, ll b){
    if(a > b) return a;
    return b;
}
vector<vector<ll>> v;
vector<coord> portals;
ll n, m, w;
vector<vector<ll>> bfs(coord c){
    //min distance starting from coordinate c
    priority_queue<pair<ll,coord>> pq;
    pq.push({0,c});
    bool visited[n][m];
    vector<vector<ll>> dist;
    //visi
    dist.resize(n);
    for(ll i = 0; i < n; i++){
        dist[i].resize(m);
        for(ll j = 0; j < m; j++){
            visited[i][j] = false;
            dist[i][j] = -pow(10,17);
        }
    }
    visited[c.x][c.y] = true;
    dist[c.x][c.y] = 0;
    vector<coord> pos;
    pos.push_back({-1,0});
    pos.push_back({0,-1});
    pos.push_back({1,0});
    pos.push_back({0,1});
    while(!pq.empty()){
        pair<ll,coord> curPr = pq.top();
        pq.pop();
        coord cur = curPr.second;
        visited[cur.x][cur.y] = true;
        //for(pair<coord,ll> nxt: possible){
            for(coord c: pos) {
                coord c1 = (coord) {cur.x  + c.x, cur.y + c.y};
                if (c1.x < n && c1.x >= 0 && c1.y < m && c1.y >= 0 && v[c1.x][c1.y] != -1) {
                    if (v[c1.x][c1.y] != -1) {
                        pair<coord,ll> nxt = {c1,w};
                        if(visited[nxt.first.x][nxt.first.y]) continue;
                        pq.push({curPr.first - nxt.second,nxt.first});
                        dist[nxt.first.x][nxt.first.y] = MA(curPr.first - nxt.second, dist[nxt.first.x][nxt.first.y]);
                        visited[nxt.first.x][nxt.first.y] = true;
                    }
                }
            }
        //}
    }
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            dist[i][j] -= 2 * dist[i][j];
        }
    }
    return dist;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ll n, m, w;
    cin >> n >> m >> w;
    v.resize(n);
    for(ll i = 0; i < n; i++) {
        v[i].resize(m);
        for (ll j = 0; j < m; j++) {
            cin >> v[i][j];
            if (v[i][j] != 0 && v[i][j] != -1) {
                portals.push_back({i, j});
            }
        }
    }
    vector<vector<ll>> distFromStart = bfs({0,0});
    vector<vector<ll>> distFromEnd = bfs({n - 1,m - 1});
    //prll(distFromEnd);
    ll myMin = distFromEnd[0][0];
    ll myMin1 = pow(10,17);
    ll myMin2 = pow(10,17);
    for(coord c1: portals){
        if(distFromStart[c1.x][c1.y] != pow(10,17)){
            myMin1 = min(distFromStart[c1.x][c1.y] + v[c1.x][c1.y], myMin1);
        }
        if(distFromEnd[c1.x][c1.y] != pow(10,17)) {
            myMin2 = min(distFromEnd[c1.x][c1.y] + v[c1.x][c1.y], myMin2);
        }
    }
    myMin = min(myMin1 + myMin2, myMin);
    if(myMin == pow(10,17)){
        cout << -1 << endl;
        return 0;
    }
    cout << myMin << endl;
}
