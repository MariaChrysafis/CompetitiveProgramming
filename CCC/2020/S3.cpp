#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <ctime>
#include <set>
#include <algorithm>
#include <iomanip>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;
const int MOD1 = 1e9 + 9;
ll binPow (ll x, ll y, int mod) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res;
            ans %= mod;
        }
        res *= res;
        res %= mod;
        y >>= 1;
    }
    return ans;
}
const int THING = 10009;
int main() {
    //freopen("art2.in", "r", stdin);
    string s, t;
    cin >> s >> t;
    if (s.length() > t.length()) {
        cout << 0;
        return 0;
    }
    vector<int> oc(26);
    vector<int> oc_des(26);
    int arr[26];
    for (int i = 0; i < 26; i++) {
        arr[i] = i + 3;
    }
    ll soFar = 0;
    ll soFar1 = 0;
    for (int i = 0; i < s.length(); i++) {
        oc[t[i] - 'a']++;
        oc_des[s[i] - 'a']++;
        soFar = THING * soFar + arr[t[i] - 'a'];
        soFar1 = THING * soFar1 + arr[t[i] - 'a'];
        soFar %= MOD;
        soFar1 %= MOD1;
    }
    set<ll> mySet;
    for (int i = 0; i <= t.length() - s.length(); i++) {
        if (oc == oc_des) {
            mySet.insert(soFar1 * soFar);
        }
        if (i == t.length() - s.length()) {
            break;
        }
        oc[t[i] - 'a']--;
        oc[t[i + s.length()] - 'a']++;
        soFar -= (binPow(THING, (int)s.length() - 1, MOD) * arr[t[i] - 'a']) % MOD - MOD, soFar %= MOD, soFar *= THING, soFar %= MOD, soFar += arr[t[i + s.length()] - 'a'], soFar %= MOD;
        soFar1 -= (binPow(THING, (int)s.length() - 1, MOD1) * arr[t[i] - 'a']) % MOD1 - MOD1, soFar1 %= MOD1, soFar1 *= THING, soFar1 %= MOD1, soFar1 += arr[t[i + s.length()] - 'a'], soFar1 %= MOD1;

    }
    cout << mySet.size() << endl;
}
