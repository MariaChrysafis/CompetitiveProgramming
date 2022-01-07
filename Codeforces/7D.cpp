#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>

#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

ll mult (ll x, ll y) {
    return (x * y) % MOD;
}

ll add (ll x, ll y) {
    if (y < 0) {
        y = MOD + y;
    }
    return (x + y) % MOD;
}

vector<int> powr, ipowr;

string s;
vector<int> hashing, hashingR;
const int base = 20;

ll get_hash (int l, int r) {
    return mult(add(hashing[r + 1], - hashing[l]), ipowr[l]);
}

ll get_hashR (int l, int r) {
    return add(hashingR[r + 1], - mult(hashingR[l], powr[r - l + 1]));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s;
    powr.push_back(1), ipowr.push_back(1);
    while (powr.size() != s.length() + 5) {
        powr.push_back(mult(powr.back(), base));
        ipowr.push_back(mult(ipowr.back(), 140000001));
    }
    hashing.push_back(0);
    for (int i = 0; i < s.length(); i++) {
        hashing.push_back(add(hashing.back(), mult(powr[i], s[i] - 'a' + 1)));
    }
    hashingR.push_back(0);
    for (int i = 0; i < s.length(); i++) {
        hashingR.push_back(add(mult(hashingR.back(), base), s[i] - 'a' + 1));
    }
    ll dp[s.length()];
    dp[0] = 1;
    for (int i = 1; i < s.length(); i++) {
        int mid = (i - 1)/2;
        if (i % 2 == 1) {
            if (get_hash(0, mid) != get_hashR(mid + 1, i)) {
                dp[i] = 0;
                continue;
            }
        } else {
            if (get_hash(0, (i - 1)/2) != get_hashR((i - 1)/2 + 2, i)) {
                dp[i] = 0;
                continue;
            }
        }
        dp[i] = dp[mid] + 1;
    }
    ll ans = 0;
    for (int i = 0; i < s.length(); i++) {
        ans += dp[i];
    }
    cout << ans;
}
