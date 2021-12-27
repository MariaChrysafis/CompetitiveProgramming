#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

typedef int64_t ll;

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

vector<ll> fact;

ll inv (ll x) {
    return binPow(x, MOD - 2);
}

ll combo (ll x, ll y) {
    //cout << x << " " << y << '\n';
    if (x < y) {
        return 0;
    }
    return mult(fact[x], inv(mult(fact[x - y], fact[y])));
}

string s;

int cnt0 (int l, int r) {
    int cnt = 0;
    for (int i = l; i <= r; i++) {
        cnt += (s[i] == '0');
    }
    return cnt;
}

int cnt1 (int l, int r) {
    return r - l + 1 - cnt0(l, r);
}

vector<pair<int,int>> remove_overlaps (vector<pair<int,int>> vec) {
    vector<pair<int,int>> valid;
    for (int i = 0; i < vec.size(); i++) {
        bool overlap = false;
        for (int j = 0; j < vec.size(); j++) {
            if (i == j) {
                continue;
            }
            if (vec[j].first <= vec[i].first && vec[j].second >= vec[i].second) {
                overlap = true;
            }
        }
        if (!overlap) {
            valid.push_back(vec[i]);
        }
    }
    return valid;
}

void solve() {
    int n, k;
    cin >> n >> k;
    cin >> s;
    vector<pair<int,int>> vec;
    for (int i = 0; i < s.length(); i++) {
        vec.emplace_back(i, -1);
        int cur = 0;
        for (int j = i; j < s.length(); j++) {
            cur += (s[j] - '0');
            if (cur == k) {
                vec.back().second = max(vec.back().second, j);
            }
        }
        if (vec.back().second == -1) {
            vec.pop_back();
        }
    }
    if (k == 0) {
        cout << 1 << '\n';
        return;
    }
    vec = remove_overlaps(vec);
    ll ans = 0;
    for (int i = 0; i < vec.size(); i++) {
        int len = vec[i].second - vec[i].first + 1;
        int ones = k;
        int zeroes = len - k;
        // cout << ans << " " << ones + zeroes << " " << ones << " " << combo(ones + zeroes, ones) << '\n';
        ans += combo(ones + zeroes, ones);
        if (i != 0) {
            ones = cnt1(vec[i].first, vec[i - 1].second);
            zeroes = cnt0(vec[i].first, vec[i - 1].second);
        } else {
            ones = zeroes = 1;
            zeroes = -1;
        }
        ans -= combo(ones + zeroes, ones);
        ans += MOD;
        ans %= MOD;
    }
    if (ans == 0) {
        ans = 1;
    }
    cout << ans << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    while (fact.size() != 5000) {
        fact.push_back(mult(fact.back(), fact.size()));
    }
    solve();

}
