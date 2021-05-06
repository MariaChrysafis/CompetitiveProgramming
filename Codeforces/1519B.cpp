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
bool solve(){
    ll n, m, k;
    cin >> n >> m >> k;
    //an + bm = k
    return (n * m - 1 == k);
}
int main(){
    int t;
    cin >> t;
    while(t--){
        bool b = solve();
        if(b) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
