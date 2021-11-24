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
ll powr (ll x) {
    ll ans = 1;
    for (int i = 0; i < x; i++) {
        ans *= 2;
        ans %= MOD;
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> arr(n);
    int oc[31];
    for (int i = 0; i <= 30; i++) {
        oc[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        int a = arr[i];
        int cntr = 0;
        while (a % 2 == 0) {
            a /= 2, cntr++;
        }
        oc[cntr]++;
    }
    ll res = 0;
    for (int i = 1; i <= 30; i++) {
        if (oc[i] == 0) {
            continue;
        }
        //gcd is pow(2, i)
        ll ans = 0;
        for (int j = i + 1; j <= 30; j++) {
            ans += oc[j];
            ans %= MOD;
        }
        res += (powr(oc[i] - 1) * powr(ans)) % MOD;
        res %= MOD;
    }
    cout << (powr(n) - res - 1 + 2 * MOD) % MOD;

}
