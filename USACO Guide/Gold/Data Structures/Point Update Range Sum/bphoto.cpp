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
    freopen("bphoto.in", "r", stdin);
    freopen("bphoto.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(n);
    set<int> s;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s.insert(v[i]);
    }
    map<int,int> myMap;
    int cntr = 0;
    for (int i: s) {
        myMap[i] = cntr++;
    }
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
    }
    segmentTree st1;
    segmentTree st2;
    st1.resz(n + 5), st2.resz(n + 5);
    for (int i = 0; i < n; i++) {
        st2.update(v[i], 1);
        //cout << v[i] << " ";
    }
    //cout << endl;
    cntr = 0;
    for (int i = 0; i < n; i++) {
        int l = st1.query(v[i] + 1, n + 1);
        int r = st2.query(v[i] + 1, n + 1);
        //cout << l << " " << r << endl;
        cntr += (max(l, r) > 2 * min(l, r));
        st1.update(v[i], 1);
        st2.update(v[i], -1);
    }
    cout << cntr;
}
