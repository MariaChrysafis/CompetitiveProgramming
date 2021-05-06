#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
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
void print(vector<ll> v){
    for(ll i: v){
        cout << i << " ";
    }
    cout << endl;
}
ll sum(vector<ll> v){
    ll sm = 0;
    for(ll i: v){
        sm += i;
    }
    return sm;
}
vector<ll> suffix(vector<ll> v){
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<ll> suf;
    suf.push_back(0);
    suf.push_back(v[v.size() - 1]);
    for(int i = v.size() - 2; i >= 0; i--){
        suf.push_back(suf.back() + v[i]);
    }
    //reverse(suf.begin(), suf.end());
    return suf;
}
void solve(){
    ll n;
    cin >> n;
    ll u[n];
    ll s[n];
    for(int i = 0; i < n; i++){
        cin >> u[i];
    }
    for(int i = 0; i < n; i++){
        cin >> s[i];
    }
    map<int,vector<ll>> myMap;
    map<int,ll> mySum;
    for(int i = 0; i < n; i++){
        myMap[u[i]].push_back(s[i]);
    }
    map<int,vector<ll>> mySuf;
    for(pair<int,vector<ll>> p: myMap){
        mySuf[p.first] = suffix(p.second);
        mySum[p.first] = mySuf[p.first][mySuf[p.first].size() - 1];
        //print(mySuf[p.first]);
    }
 
    vector<ll> ans(n);
    for(int i = 0; i < n; i++)
        ans[i] = 0;
    for(pair<int,ll> p: mySum){
        for(int k = 1; k <= n; k++){
            int x = p.first;
            ll y = p.second;
            ans[k - 1] += y - mySuf[x][(mySuf[x].size() - 1) % k];
            if(mySuf[x].size() - 1 < k) break;
        }
    }
    print(ans);
    return;
 
}
int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
