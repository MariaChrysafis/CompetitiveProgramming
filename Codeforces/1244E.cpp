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
vector<ll> a;
int binSearchLess (ll x) {
    if (a.back() < x) {
        return a.size();
    }
    if (a[0] >= x) {
        return 0;
    }
    //how many elements are < x
    int l = 0;
    int r = a.size() - 1;
    while (l < r) {
        int mid = (l + r + 1)/2;
        if (a[mid] < x) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    return l + 1;
}
int binSearchMore (ll x) {
    //how many elements are greater than x
    if (a.back() < x) {
        return 0;
    }
    if (a[0] > x) {
        return a.size();
    }
    int l = 0;
    int r = a.size() - 1;
    while (l < r) {
        int mid = (l + r)/2;
        if (a[mid] > x) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return (a.size() - l);
}
vector<ll> pref;
ll cost1 (ll l) {
    //how many to get everything >= l
    if (a[0] >= l) return 0;
    ll less = binSearchLess(l);
    return less * l - pref[less];
}
ll cost2 (ll r) {
    //how many to get everything <= r
    if (a.back() <= r) return 0;
    ll more = binSearchMore(r);
    return pref.back() - pref[pref.size() - more - 1] - more * r;
}
ll cost (ll l, ll r) {
    //cost to get everything >= l and <= r
    return cost2(r) + cost1(l);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    pref.push_back(0);
    for (int i = 0; i < n; i++) {
        pref.push_back(pref.back() + a[i]);
    }
    ll myMin = 1e9;
    for (int i = 0; i < n; i++) {
        ll l = a[i] + 1;
        ll r = 1e10;
        while (l < r) {
            ll mid = (l + r )/2;
            //minimize a[i]
            if (cost(a[i], mid) <= k) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        if (l != r) continue;
        if (cost(a[i], l) <= k) {
            myMin = min(myMin, l - a[i]);
        }
        myMin = min(myMin, l - a[i]);
    }
    for (int i = 0; i < n; i++) {
        ll l = a[0];
        ll r = a[i] - 1;
        while (l < r) {
            ll mid = (l + r + 1)/2;
            if (cost(mid, a[i]) <= k) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        if (l != r) continue;
        if (cost(l, a[i]) <= k) {
            myMin = min(myMin, a[i] - l);
        }
    }
    for (int i = 0; i < n; i++) {
        if (cost(a[i], a[i]) <= k) {
            myMin = 0;
        }
    }
    cout << myMin;

}
