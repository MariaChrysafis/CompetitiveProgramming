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
ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= MOD;
        }
        res *= res;
        res %= MOD;
        y /= 2;
    }
    return ans;
}
const int sz = 100001;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> arr(n);
    vector<ll> oc(sz);
    oc.assign(oc.size(), 0);
    map<int,int> myMap;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        myMap[arr[i]]++;
    }
    for (int i = 1; i < oc.size(); i++) {
        for (int j = i; j < oc.size(); j += i) {
            oc[i] += myMap[j];
        }
    }
    vector<ll> lpf(sz);
    lpf.assign(sz, 0);
    for (int i = 2; i < sz; i++) {
        if (!lpf[i]) {
            for (int j = i; j < sz; j += i) {
                if (!lpf[j]) {
                    lpf[j] = i;
                }
            }
        }
    }
    vector<ll> mobius(sz);
    for (int i = 1; i < sz; i++) {
        if (i == 1) mobius[i] = 1;
        else {
            if (lpf[i/lpf[i]] == lpf[i]) mobius[i] = 0;
            else mobius[i] = -1 * mobius[i/lpf[i]];
        }
    }
    //vector<ll> g(sz);
    int ans = 0;
    for (int i = 1; i < sz; i++) {
        ans += (mobius[i] * (binPow(2, oc[i]) - 1) + MOD) % MOD;
        ans %= MOD;
    }
    cout << ans;

}
