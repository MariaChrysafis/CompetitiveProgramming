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
int gcd (int a, int b) {
    if (min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
template<class T> struct Seg { // comb(ID,b) = b
    const T ID = 0; T comb(T a, T b) { return a + b; }
    int n; vector<T> seg;
    void init(int _n) { n = _n; seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = comb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// min on interval [l, r]
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = comb(ra,seg[l++]);
            if (r&1) rb = comb(seg[--r],rb);
        }
        return comb(ra,rb);
    }
};
ll solver (vector<ll> v) {
    bool isPrime[v.size()];
    for (int i = 0; i < v.size(); i++) {
        isPrime[i] = true;
        for (int j = 2; j <= sqrt(v[i]); j++) {
            if (v[i] % j == 0) {
                isPrime[i] = false;
            }
        }
    }
    Seg<ll> st;
    st.init(v.size() + 2);
    for (int i = 0; i < v.size(); i++) {
        st.upd(i, v[i]);
    }
    ll ans = 0;
    for (int i = 0; i < v.size(); i++) {
        if (!isPrime[i] || v[i] == 1) {
            continue;
        }
        ll left = 0;
        if (i == 0 || v[i - 1] != 1) {
            left = 0;
        } else {
            ll l = 0;
            ll r = i - 1;
            while (l < r) {
                int mid = (l + r)/2;
                if (st.query(mid, i - 1) == i - 1 - mid + 1) {
                    //then all ones
                    r = mid;
                } else {
                    //then not all ones
                    l = mid + 1;
                }
            }
            left = i - 1 - l + 1;
        }
        ll right = 0;
        if (i == v.size() - 1 || v[i + 1] != 1) {
            right = 0;
        } else {
            ll l = i + 1;
            ll r = v.size() - 1;
            while (l < r) {
                int mid = (l + r + 1)/2;
                if (st.query(i + 1, mid) == mid - i - 1 + 1) {
                    //then all ones
                    l = mid;
                } else {
                    //then not all ones
                    r = mid - 1;
                }
            }
            right = l - (i + 1) + 1;
        }
        ans += (left + 1) * (right + 1) - 1;
    }
    return ans;
}
void solve() {
    ll n, e;
    cin >> n >> e;
    vector<ll> arr(n);
    vector<vector<ll>> v(e);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        v[i % e].push_back(arr[i]);
    }
    ll ans = 0;
    for (int i = 0; i < e; i++) {
        ll cntr = solver(v[i]);
        ans += cntr;
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
}
