#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;
ll powr (ll x, ll y) {
    if (y == 0) return 1;
    ll res = powr(x, y - 1);
    if (res > 1e18/x) return -1;
    return res * x;
}
vector<vector<ll>> factorizations (ll N) {
    if (N == 1) {
        return {{1}};
    }
    vector<vector<ll>> ans;
    for (int i = 2; i <= N - 1; i++) {
        if (N % i == 0) {
            vector<vector<ll>> vec = factorizations(i);
            for (int j = 0; j < vec.size(); j++) {
                vec[j].push_back(N/i);
            }
            for (auto& v: vec) {
                ans.push_back(v);
            }
        }
    }
    if (ans.empty()) {
        return {{N}};
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<ll> primes {2, 3, 5, 7, 11, 13, 17, 19, 21, 23, 29};
    int N;
    cin >> N;
    vector<vector<ll>> v = factorizations(N);
    ll ans = 1e18;
    for (auto& vec: v) {
        sort(vec.begin(), vec.end());
        reverse(vec.begin(), vec.end());
        if (vec[0] > 60) {
            continue;
        }
        ll mult = 1;
        bool fine = false;
        for (int i = 0; i < vec.size(); i++) {
            mult *= powr(primes[i], vec[i] - 1);
            if (mult < 0) fine = true;
        }
        if (!fine) {
            ans = min(ans, mult);
        }
    }
    cout << ans;
}
