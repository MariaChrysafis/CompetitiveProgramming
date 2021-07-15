#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
vector<int> fact;
const long long MAX = 3e5;
const long long MOD = 998244353;
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long add(long long a, long long b){
    return (a + b) % MOD;
}
long long binPow(long long a, long long b){
    long long res = a;
    long long ans = 1;
    while(b > 0){
        if(b & 1){
            ans = mult(ans, res);
        }
        b /= 2;
        res = mult(res, res);
    }
    return ans;
}
long long inv(long long a){
    return binPow(a, MOD - 2);
}
long long combo(long long a, long long b){
    if(a < b) return 0;
    if(a == b) return 1;
    return mult(fact[a], inv(mult(fact[b], fact[a - b])));
}
void solve(){
    vector<pair<int,bool>> intervals; //0 -> start
    int n, k;
    cin >> n >> k;
    for(int i = 0; i < n; i++){
        int u, v;
        cin >> u >> v;
        intervals.push_back({u, 0});
        intervals.push_back({v, 1});
    }
    sort(intervals.begin(), intervals.end());
    long long cur = 0;
    long long ans = 0;
    for(int i = 0; i < intervals.size(); i++){
        if(intervals[i].second == 1){
            cur--;
        }else{
            cur++;
            ans = add(combo(cur - 1, k - 1), ans);
        }
    }
    cout << ans << endl;
}
int main() {
    fact.push_back(1);
    int ind = 1;
    while(fact.size() != MAX){
        fact.push_back(mult(fact.back(), ind++));
    }
    solve();
}
