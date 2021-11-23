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
#define ll int64_t
using namespace std;
const int MOD = 998244353;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return (a + b) % MOD;
    }

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return op(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] += y;
            val[cur] %= MOD;
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = 2 * curY - curX + 1;
            } else {
                curX = 2 * curX - curY - 1;
            }
            cur /= 2;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<pair<ll,ll>> vec;
    for (int i = 0; i < arr.size(); i++) {
        vec.push_back({arr[i], -i});
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; i++) {
        arr[-vec[i].second] = i + 1;
    }
    segmentTree st;
    st.resz(n + 2);
    st.update(n + 1, 1);
    for (int i = 0; i < n; i++) {
        st.update(i, 0);
    }
    for (int i = 0; i < n; i++) {
        st.update(arr[i], st.query(0, arr[i] - 1) + 1);
    }
    cout << st.query(0, n + 1);
}
