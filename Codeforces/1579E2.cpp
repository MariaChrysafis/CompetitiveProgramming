#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <cmath>
#include <cassert>

#define ll long long

using namespace std;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return a + b;
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
            val[cur] = query(curX, curY) + y;
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


void solve () {
    int n;
    cin >> n;
    vector<int> v(n);
    map<int,int> myMap;
    map<int,int> conv;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        myMap[v[i]]++;
    }
    segmentTree st;
    st.resz(n + 10);
    int cntr = 0;
    for(pair<int,int> p: myMap) {
        conv[p.first] = cntr;
        cntr++;
    }
    for(int i = 0; i < n; i++) {
        v[i] = conv[v[i]];
    }
    st.update(v[0], 1);
    long long ans = 0;
    for(int i = 1; i < v.size(); i++) {
        long long less = st.query(0, v[i] - 1);
        long long greater = st.query(v[i] + 1, n + 7);
        ans += min(less, greater);
        st.update(v[i], 1);
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

}
