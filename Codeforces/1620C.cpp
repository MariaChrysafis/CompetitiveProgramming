#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
typedef long long ll;

using namespace std;
void solve() {
    ll n, k, x;
    cin >> n >> k >> x;
    string s;
    cin >> s;
    vector<pair<char,ll>> v;
    v.push_back({s[0], 1});
    for (ll i = 1; i < n; i++) {
        if (v.back().first == s[i]) {
            v.back().second++;
        } else {
            v.push_back({s[i], 1});
        }
    }
    ll suf[v.size() + 1];
    for (ll i = 0; i <= v.size(); i++) {
        suf[i] = 1;
    }
    for (ll i = v.size() - 1; i >= 0; i--) {
        suf[i] = suf[i + 1];
        if (v[i].first == 'a') continue;
        if (LLONG_MAX/suf[i] < k * v[i].second + 1) {
            suf[i] = LLONG_MAX;
            continue;
        }
        suf[i] *= (k * v[i].second + 1);
        //cout << suf[i] << ' ';
    }
    string ans = "";
    for (ll i = 0; i < v.size(); i++) {
        if (v[i].first == 'a') {
            while (v[i].second--) {
                ans += 'a';
            }
        } else {
            ll fin = 0;
            for (ll j = 0; j <= k * v[i].second + 1; j++) {
                fin = suf[i + 1] * (j + 1);
                if (fin >= x) {
                    ll dum = j;
                    while (dum--) {
                        ans += 'b';
                    }
                    x -= (suf[i + 1] * j);

                    break;
                }
            }
        }
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
