#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>

#define ll long long
using namespace std;

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
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        return query(dum, tl, mid, l, r) + query(dum + 1, mid + 1, tr, l, r);
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
segmentTree st;
int binSearch (int l, int r, int x) {
    //What's the xth element in the list?
    int m = (l + r)/2;
    if (l == r) {
        return l;
    }
    if (st.query(0, m) >= x) {
        return binSearch(l, m, x);
    } else {
        return binSearch(m + 1, r, x);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    st.resz(v.size());
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        st.update(i, 1);
    }
    for (int i = 0; i < n; i++) {
        int pos;
        cin >> pos;
        int x = binSearch(0, n - 1, pos);
        cout << v[x] << " ";
        st.update(x, -1);
    }
}
