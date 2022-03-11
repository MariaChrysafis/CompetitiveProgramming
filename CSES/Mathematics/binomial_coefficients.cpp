#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <ctime>
#include <cstdlib>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
 
using namespace std;
const int MOD = 1e9 + 7;
int64_t binPow (int64_t x, int y) {
    int64_t ans = 1;
    int64_t res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res; res %= MOD;
        y >>= 1;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
int main() {
    //freopen("inp.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<int64_t> fact = {1};
    while (fact.size() != (int)1e6 + 1) {
        fact.push_back(fact.back() * fact.size());
        fact.back() %= MOD;
    }
    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        cout << (fact[x] * inv((fact[x - y] * fact[y]) % MOD)) % MOD << '\n';
    }
}
