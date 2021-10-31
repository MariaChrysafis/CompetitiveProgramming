#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <map>
#define ll long long
#pragma GCC optimize("Ofast")
using namespace std;
const int MOD = 998244353;
void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ll ans = 0;
    unordered_map<int,int> prev_cnt;
    prev_cnt[arr[n - 1]]++;
    for (int i = n - 2; i >= 0; i--) {
        unordered_map<int,int> cur_cnt;
        cur_cnt[arr[i]]++;
        cur_cnt.reserve(2000);
        for (auto& p: prev_cnt) {
            int cost = (arr[i] + p.first - 1)/p.first;
            cur_cnt[arr[i]/cost] += p.second;
            ans += ((ll)p.second * (cost - 1)) % MOD * (i + 1);
            ans %= MOD;
        }
        prev_cnt = cur_cnt;
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
