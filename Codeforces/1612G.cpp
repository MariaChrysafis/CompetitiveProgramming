#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
vector<int64_t> fact;
const int MOD = 1e9 + 7;
int res (vector<int> &vec) {
    int64_t cnt[(int)1e6 + 1];
    for (int i = 0; i <= 1e6; i++) {
        cnt[i] = 0;
    }
    for (int i: vec) {
        cnt[i]++;
    }
    int64_t ans = 1;
    for (int i = 1e6; i >= 1; i--) {
        ans *= (i == 1) ? fact[cnt[i]] : (fact[cnt[i]] * fact[cnt[i]]) % MOD, ans %= MOD;
        if (i >= 2) cnt[i - 2] += cnt[i];
    }
    return ans;
}
int dist (vector<int>& vec) {
    int64_t cnt[(int)1e6 + 1];
    for (int i = 0; i <= 1e6; i++) {
        cnt[i] = 0;
    }
    int64_t tot = 0;
    for (int i: vec) {
        cnt[i]++, tot += i;
        tot %= MOD;
    }
    tot %= MOD;
    int64_t ans = 0;
    for (int i = 1e6; i >= 2; i--) {
        while (tot <= cnt[i]) {
            tot += MOD;
        }
        ans += (((i - 1) * cnt[i]) % MOD * (tot - cnt[i]) % MOD) % MOD, ans %= MOD;
        tot -= 2 * cnt[i];
        cnt[i - 2] += cnt[i];
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact.push_back(1);
    for (int i = 0; i <= (int)1e6; i++) {
        fact.push_back(fact.back() * fact.size());
        fact.back() %= MOD;
    }
    vector<int> vec;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        vec.push_back(x);
    }
    cout << dist(vec) << " " << res(vec);
}
