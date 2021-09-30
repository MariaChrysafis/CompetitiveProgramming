#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

const int MOD = 1e9 + 7;
vector<int> isPrime;
vector<int> mu;

long long mult(long long a, long long b) {
    return (a * b) % MOD;
}

long long binPow(long long a, long long b) {
    long long ans = 1;
    long long res = a;
    while(b > 0) {
        if(b & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        b >>= 1;
    }
    return ans;
}

void solve () {
    int k;
    cin >> k;
    set<int> factors;
    for(int i = 1; i <= sqrt(k); i++) {
        if(k % i == 0) {
            factors.insert(i), factors.insert(k/ i);
        }
    }
    long long ans = 0;
    for(int d: factors) {
        ans += mult(binPow(2, k/d), mu[d]);
        if(ans >= MOD) ans -= MOD;
    }
    cout << (binPow(2, k) - ans + MOD) % MOD << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    isPrime.resize(1e6 + 10);
    mu.resize(1e6 + 10);
    for(int i = 0; i < isPrime.size(); i++) {
        isPrime[i] = i;
        mu[i] = 1;
    }
    for(int i = 2; i < isPrime.size(); i++) {
        if(isPrime[i] == i) {
            for(int j = 2 * i; j < isPrime.size(); j += i) {
                if(isPrime[j] != i) {
                    isPrime[j] = i;
                }
            }
        }
    }
    for (int i = 1; i < isPrime.size(); i++) {
        if(i == 1) {
            mu[i] = 1;
        } else {
            if(isPrime[i/isPrime[i]] == isPrime[i]) {
                mu[i] = 0;
            } else {
                mu[i] = -1 * mu[i/isPrime[i]];
            }
        }
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
