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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    segmentTree st;
    st.resz((int)1e5 + 10);
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        v[i] = st.query(arr[i] + 1, (int)1e5);
        st.update(arr[i], 1);
    }
    segmentTree st1;
    st1.resz((int)1e5 + 10);
    vector<ll> ans(n);
    long long val = 0;
    for (int i = 0; i < n; i++) {
        ans[i] = st1.query(arr[i] + 1, (int)1e5);
        st1.update(arr[i], v[i]);
        val += ans[i];
    }
    cout << val;
}
