#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#define ll long long
using namespace std;
ll gcd (ll a, ll b) {
    if(min(a,b) == 0) return max(a,b);
    return gcd(max(a,b) % min(a,b), min(a,b));
}
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll query(int dum, int tl, int tr, int& l, int& r) {
        if (tr < l || tl > r) {
            return ID;
        }
        if (tl >= l && tr <= r) {
            return val[dum];
        }
        int mid = (tl + tr) >> 1;
        dum = dum << 1;
        return gcd(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = gcd(gcd(query(curX, x - 1), query(x + 1, curY)), y);
            if (cur == 0) {
                break;
            }
            if(cur % 2 == 0) {
                curY = (curY << 1) - curX + 1;
            } else {
                curX = (curX << 1) - curY - 1;
            }
            cur >>= 1;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }
};

segmentTree st;

int binSearch(int left, int l, int r) {
    int m = (l + r) >> 1;
    if (l == r) {
        return l;
    }
    if(st.query(left, m) != 1) {
        return binSearch(left, m + 1, r);
    } else {
        return binSearch(left, l, m);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    st.resz(n);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        st.update(i, x);
    }
    int l = 0;
    int r = 0;
    int myMin = 1e9;
    while (r != n) {
        if(st.query(l, r) != 1) {
            r++;
            continue;
        } else {
            myMin = min(myMin, r - l + 1);
            l++;
        }
    }
    if(myMin == 1e9) {
        cout << -1;
        return 0;
    }
    cout << myMin;
}
