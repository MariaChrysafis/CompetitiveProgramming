#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <stack>
#include <map>
#include <set>
using namespace std;
long long MOD = 1000000007;
long long MAX = 3000000;
long long powr(long long x, long long y){
    long long mi = 1;
    while(y > 0){
        if(y & 1){
            mi = (mi * x) % MOD;
        }
        x = (x * x) % MOD;
        y >>= 1;
    }
    return mi;
}
long long mult(long long a, long long b){
    return (a * b) % MOD;
}
long long inv(long long a){
    return powr(a, MOD - 2);
}
vector<long long> fact;
long long combo(long long n, long long r){
    if(r < 0) return 0;
    if(r > n) return 0;
    return mult(mult(fact[n], inv(fact[r])), inv(fact[n - r]));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long N, M, K;
    cin >> N >> M >> K;
    fact.push_back({1});
    for(int i = 1; i < MAX; i++){
        fact.push_back(mult(fact[i - 1], i));
    }
    if(N <= K){
        cout << combo(N + M, M) << endl;
        return 0;
    }
    if(N > M + K){
        cout << 0 << endl;
        return 0;
    }
    cout << (combo(N + M, M) - combo(N + M, M + K + 1) + MOD) % MOD << endl;
}
