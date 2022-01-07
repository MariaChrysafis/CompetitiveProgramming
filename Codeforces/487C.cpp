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

bool isPrime (int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

ll binPow (ll x, ll y, int MOD) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}

ll inv (ll x, ll MOD) {
    return binPow(x, MOD - 2, MOD);
}
set<int> unused;
vector<int> valid (int n) {
    for (int i = 1; i < n; i++) {
        unused.insert(i);
    }
    vector<int> ans = {1};
    int prev = 1; unused.erase(prev);
    set<int> used = {1};
    set<int> s = {ans[0]};
    for (int i = 2; i < n; i++) {
        int cur = -1;
        for (int j: unused) {
            if (!s.count((j * inv(prev, n)) % n)) {
                cur = j;
                break;
            }
        }
        if (cur == -1) {
            return {};
        }
        unused.erase(cur);
        used.insert(cur);
        ans.push_back((cur * inv(prev, n)) % n);
        s.insert(ans.back());
        prev = cur;
    }
    ans.push_back(n);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    if (n == 1) {
        cout << "YES\n1\n";
        return 0;
    }
    if (n == 4) {
        cout << "YES\n1\n3\n2\n4\n";
        return 0;
    }
    if (!isPrime(n)) {
        cout << "NO\n";
        return 0;
    }
    int t = 100;
    while (t--) {
        vector<int> v = valid(n);
        if (!v.empty()) {
            cout << "YES\n";
            for (int j: v) {
                cout << j << '\n';
            }
            return 0;
        }
    }
    cout << "NO\n";
}
