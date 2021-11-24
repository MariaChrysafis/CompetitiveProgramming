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
ll gcd (ll a, ll b) {
    if (min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
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
    for (int i = 0; i < 3; i++) {
        //cout << oc[i] << ' ';
    }
    //cout << '\n';
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
        ll add = (powr(oc[i] - 1) * powr(ans)) % MOD;
        //cout << powr(oc[i] - 1) * powr(ans) << '\n';
        res += add;
        res %= MOD;
    }
    cout << (powr(n) - res - 1 + 2 * MOD) % MOD;
    return 0;

    for (int i = 0; i < (1 << n); i++) {
        int g = 0;
        int sum = 0;
        bool allEven = true;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) {
                g = gcd(g, arr[j]);
                sum += arr[j] * (arr[j] - 1)/2;
                if (arr[j] % 2 == 1) {
                    allEven = false;
                }
            }
        }
        int largestPowerOfTwo = 0;
        for (int p = 0; p < n; p++) {
            if (g % (1 << p) == 0) {
                largestPowerOfTwo = (1 << (p + 1));
            } else {
                break;
            }
        }
        if (!(g != 0 && sum % g == 0)) {
            for (int j = 0; j < n; j++) {
                if ((1 << j) & i) {
                    cout << arr[j] % largestPowerOfTwo << ' ';
                }
            }
            cout << '\n';
        }
    }

}
