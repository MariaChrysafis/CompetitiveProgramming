#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <map>
#include <algorithm>
#define ll long long
using namespace std;
vector<long long> fact;
const int MOD = 998244353;
long long binPow(long long x, long long y){
    long long ans = 1;
    long long res = x;
    while(y > 0){
        if(y & 1){
            ans = (ans * res) % MOD;
        }
        res = (res * res) % MOD;
        y /= 2;
    }
    return ans;
}
long long inv(long long x){
    return binPow(x, MOD - 2);
}
long long combo(long long x, long long y){
    return (fact[x] * inv((fact[y] * fact[x - y]) % MOD)) % MOD;
}
void solve(){
    int n;
    cin >> n;
    vector<int> v(n);
    map<int,int> oc;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        oc[v[i]]++;
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    if(v[0] == v[1]){
        cout << fact[v.size()] << endl;
        return;
    }
    if(v[0] - 1 > v[1]){
        cout << 0 << endl;
        return;
    }
    int myMax = n - oc[v[1]] - 1;
    //cout << oc[v[1]] << endl;
    long long ans = 0;
    for(int z = 0; z <= myMax; z++){
        int x = oc[v[1]];
        int y = n - x - z - 1;
        long long delta = ((combo(n - oc[v[1]] - 1, z) * fact[x + y]) % MOD * fact[z]) % MOD;
        ans += delta;
        ans %= MOD;
    }
    cout << (fact[n] - ans + MOD) % MOD << endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    auto start = std::chrono::high_resolution_clock::now();
    fact.push_back(1);
    while(fact.size() != (int)2e5 + 10){
        fact.push_back((fact.back() * fact.size()) % MOD);
        //cout << fact.back() << " ";
    }
    int T;
    cin >> T;
    while(T--){
        solve();
    }
 
}
