#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>

#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
ll mult (ll x, ll y) {
    return (x * y) % MOD;
}
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}
vector<int> prime_factors (int n) {
    vector<int> ans;
    int fixed = sqrt(n);
    for (int i = 2; i <= fixed; i++) {
        if (n % i == 0) {
            ans.push_back(0);
            while (n % i == 0) {
                n /= i;
                ans.back()++;
            }
        }
    }
    if (n != 1) {
        ans.push_back(1);
    }
    return ans;
}
ll inv (ll x) {
    return binPow(x, MOD - 2);
}
vector<ll> fact ;
ll combo (ll x, ll y) {
    return mult(fact[x], inv(mult(fact[y], fact[x - y])));
}
ll solve (int n, int k) {
    vector<int> v = prime_factors(n);
    ll ans = 1; //2^19
    for (int i: v) {
        ans = mult(ans, combo(i + k - 1, i));
    }
    return ans;
}
int main() {
    fact = {1};
    while (fact.size() != 1e6 + 20) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        ll ans = solve(n, k);
        cout << mult(ans, binPow(2, k - 1)) << '\n';
        //cout << ans << '\n';
    }
}
