#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#define ll int

using namespace std;

const int MOD = (int) 1e9 + 7;

long long mult(long long x, long long y) {
    return (x * y) % MOD;
}

long long binPow(long long x, long long y) {
    long long ans = 1;
    long long res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y >>= 1;
    }
    return ans;
}

long long inv(long long x) {
    return binPow(x, MOD - 2);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<long long, long long>> vec(n);
    long long ans1 = 1;
    long long ans2 = 1;
    long long ans3 = 1;
    long long ans11 = 1;
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
        ans2 = mult(mult(binPow(vec[i].first, vec[i].second + 1) - 1, inv(vec[i].first - 1)), ans2);
        ans1 = mult(vec[i].second + 1, ans1);
        ans11 *= vec[i].second + 1;
        ans11 %= (2 * (MOD - 1));
    }
    for (int i = 0; i < n; i++) {
        long long dum = (vec[i].second * ans11 / 2) % (2 * (MOD - 1));
        ans3 = mult(ans3, binPow(vec[i].first, (dum) % (MOD - 1)));
    }
    cout << ans1 << " " << ans2 << " " << ans3 << endl;
}
