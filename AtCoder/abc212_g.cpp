#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

#define ll long long
using namespace std;
const int MOD = 998244353;

long long mult(long long a, long long b){
    return (a * b) % MOD;
}

long long phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) {
                n /= p;
            }
            result -= result / p;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

vector<long long> factors(long long x) {
    vector<long long> ans;
    for (long long i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            ans.push_back(i);
        }
    }
    int n = ans.size();
    for (int i = 0; i < n; i++) {
        if (ans[i] * ans[i] == x) continue;
        ans.push_back(x / ans[i]);
    }
    return ans;
}

int main() {
    map<long long, long long> count;
    long long P;
    cin >> P;
    vector<ll> fact = factors(P - 1);
    long long ans = 0;
    for (long long i: fact) {
        ans += mult(phi(i) % MOD, i % MOD);
        ans %= MOD;
    }
    cout << (ans + 1) % MOD << endl;
}
