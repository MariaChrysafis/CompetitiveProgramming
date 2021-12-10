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
struct dsu{
    vector<ll> parent;
    vector<ll> compSize;
    ll n;
    void fill(){
        parent.resize(n), compSize.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i, compSize[i] = 1;
        }
    }
    ll find_head(ll x){
        if(x == parent[x]){
            return x;
        }
        return find_head(parent[x]);
    }
    void join(ll x, ll y){
        x = find_head(x);
        y = find_head(y);
        if(x == y){
            return;
        }
        if(compSize[x] > compSize[y]){
            swap(x,y);
            //ensures that compSize[x1] <= compSize[y1]
        }
        parent[x] = y;
        compSize[y] += compSize[x];
    }
    bool comp(int x, int y){
        return (find_head(x) == find_head(y));
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    dsu d1; d1.n = n;
    dsu d2; d2.n = n;
    d1.fill(), d2.fill();
    for (ll i = 0; i < n - 1; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        if (w) d1.join(u, v);
        else d2.join(u, v);
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (d1.find_head(i) == i) {
            ans += d1.compSize[d1.find_head(i)] * (d1.compSize[d1.find_head(i)] - 1);
        }
        if (d2.find_head(i) == i) {
            ans += d2.compSize[d2.find_head(i)] * (d2.compSize[d2.find_head(i)] - 1);
        }
        ans += (d1.compSize[d1.find_head(i)] - 1) * (d2.compSize[d2.find_head(i)] - 1);
    }
    cout << ans;
}
