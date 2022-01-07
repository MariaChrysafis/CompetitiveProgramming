#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long double ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> pref = {0};
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        pref.push_back(pref.back() + a[i]);
    }
    ll ans = 0;
    map<ll, ll> oc;
    for (int i = 0; i < n; i++) {
        ans -= oc[a[i] - 1];
        ans += oc[a[i] + 1];
        oc[a[i]]++;
    }
    for (ll i = 0; i < n; i++) {
        ll val = -a[i] * (n - (i + 1) + 1) + pref.back() - pref[i];
        ans += val;
    }
    cout << setprecision(20) << ans << '\n';
}
