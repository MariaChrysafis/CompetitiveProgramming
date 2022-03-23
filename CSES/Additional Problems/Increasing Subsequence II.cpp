#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
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
            val[cur] %= (int)1e9 + 7;
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
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> s = v;
    sort(s.begin(), s.end());
    map<int,int> myMap;
    int cntr = 0;
    for (int i: s) {
        myMap[i] = cntr++;
    }
    segmentTree st;
    st.resz(n + 1);
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
        st.update(v[i], st.query(0, v[i] - 1) + 1);
    }
    ll ans = 0;
    for (int i = 0; i <= n + 5; i++) {
        ans += st.query(i, i);
        ans %= (int)1e9 + 7;
    }
    cout << ans;
}
