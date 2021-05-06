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
vector<vector<ll>> dp;
vector<ll> a;
vector<ll> b;
const ll alpha = -pow(10,12);
ll ans(int l, int r){
    if(r < l){
        dp[l][r] = 0;
        return 0;
    }
    if(r == l){
        dp[l][r] = 0;
        return 0;
    }
    if(r - l == 1){
        return 0 - a[l] * b[l] - a[r] * b[r] + a[l] * b[r] + a[r] * b[l];
    }
    if(dp[l][r] != alpha){
        return dp[l][r];
    }
    return ans(l + 1, r - 1) - a[l] * b[l] - a[r] * b[r] + a[l] * b[r] + a[r] * b[l];
}
ll dot(vector<ll> v, vector<ll> u){
    ll ans = 0;
    for(int i = 0; i < v.size(); i++){
        ans += v[i] * u[i];
    }
    return ans;
}
void solve(){
    int n;
    cin >> n;
    a.resize(n), b.resize(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    dp.resize(n);
    for(int i = 0; i < n; i++){
        dp[i].resize(n);
        for(int j = 0; j < n; j++){
            dp[i][j] = alpha;
        }
    }
    ll myMax = 0;
    for(int i = n - 1; i >= 0; i--){
        for(int j = i; j < n; j++){
            int l = i;
            int r = j;
            if(i > j) dp[i][j] = 0;
            else if(i == j) dp[i][j] = 0;
            else if(j - i == 1) dp[i][j] = 0 - a[l] * b[l] - a[r] * b[r] + a[l] * b[r] + a[r] * b[l];
            else dp[i][j] = dp[l + 1][r - 1] - a[l] * b[l] - a[r] * b[r] + a[l] * b[r] + a[r] * b[l];
            myMax = max(dp[i][j], myMax);
        }
    }
    cout << myMax + dot(a, b) << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
