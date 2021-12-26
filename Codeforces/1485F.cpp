#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

typedef long long ll;
using namespace std;
const ll MOD = 1e9 + 7;
void solve() {
    int n;
    cin >> n;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    map<ll,ll> dp;
    //initially it's all 0 and it's all empty
    dp[0] = 1;
    ll sum = 1;
    ll pref_sum = 0;
    for (int i = 0; i < v.size(); i++) {
        ll prev = dp[-pref_sum];
        dp[-pref_sum] = sum;
        sum += sum - prev, sum += 3 * MOD, sum %= MOD;
        pref_sum += v[i];
        //cout << pref_sum << " " << sum << '\n';
    }
    cout << sum << '\n';
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
