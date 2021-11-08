#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <map>
#include <set>

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
            cur >>= 1;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
int main() {
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
    }
    segmentTree st;
    st.resz(n);
    int suf = 0;
    for (int i = n - 1; i >= 0; i--) {
        st.update(v[i], 1);
        int a = st.query(0, v[i] - 1);
        if (a != 0) {
            st.update(v[i], -1);
            break;
        }
        suf++;
    }
    cout << n - suf << endl;
    for (int i = 0; i < n - suf; i++) {
        st.update(v[i], 1);
        //cout << st.query(v[i] + 1, n - 1) << " ";
        cout << st.query(0, v[i] - 1) + n - suf - i - 1;
        if (i != n - suf - 1) {
            cout << " ";
        }
    }
    //cout << suf << endl;
}
