#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

#define ll long long

using namespace std;
vector<ll> mobius;
void fill_mob (int n) {
    mobius.resize(n + 1);
    mobius[1] = 1;
    for (int i = 2; i <= n; i++) {
        int dum = i;
        int cntr = 0;
        bool fine = false;
        for (int j = 2; j <= sqrt(i) + 1; j++) {
            if (dum % j == 0) {
                dum /= j;
                cntr++;
            }
            if (dum % j == 0) {
                mobius[i] = 0;
                fine = true;
                break;
            }
        }
        if (fine) {
            continue;
        }
        if (dum != 1) {
            cntr++;
        }
        mobius[i] = pow(-1, cntr);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    fill_mob(n);
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    b[0] = 0;
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = a[i] - b[i];
    }
    vector<ll> resp;
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        ll delta = -v[i];
        for (int j = i; j < n; j += i + 1) {
            v[j] += delta;
        }
        if (mobius[i + 1] != 0) {
            resp.push_back(delta/mobius[i + 1]);
        } else {
            tot += abs(delta);
        }
    }
    sort(resp.begin(), resp.end());
    vector<ll> pref = {0};
    for (int i = 0; i < resp.size(); i++) {
        pref.push_back(pref.back() + resp[i]);
    }
    int Q;
    cin >> Q;
    while (Q--) {
        ll x;
        cin >> x;
        int l = 0;
        int r = (int)resp.size() - 1;
        if (x + resp.back() < 0) {
            cout << tot - x * resp.size() - pref.back() << '\n';
            continue;
        }
        while (l < r) {
            int mid = (l + r)/2;
            if (x + resp[mid] >= 0) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        ll ans = tot - x * l + x * (resp.size() - l);
        ans -= pref[l];
        ans += pref.back() - pref[l];
        cout << ans << '\n';
    }
}
