#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
using namespace std;
const int MOD = 998244353;
const int MAX =1e5 + 1;
vector<int> fact;
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long binpow(long long x, long long y){
    long long res = x;
    long long ans = 1;
    while(y > 0){
        if(y & 1){
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
long long inv(long long a){
    return binpow(a, MOD - 2);
}
long long combo(long long a, long long b){
    return (fact[a] * inv((mult(fact[b], fact[a - b])))) % MOD;
}
int dif(vector<int> v, int x){
    int cur = 0;
    for(int i: v){
        cur += abs(i - x);
    }
    return cur;
}
void solve(){
    map<long long, long long> oc;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        oc[a]++;
    }
    vector<long long> v;
    for(pair<long long,long long> p: oc){
        v.push_back(p.second);
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    long long myMax = 0;
    for(int i = 0; i < v.size(); i++){
        myMax = max(myMax, v[i] * (i + 1));
    }
    cout << n - myMax << endl;
}
int main() {
    //cout << binpow(3, 3) << endl;
    fact.push_back(1);
    int x = 1;
    while(fact.size() != MAX){
        fact.push_back(mult(fact.back(), x));
        x++;
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}
