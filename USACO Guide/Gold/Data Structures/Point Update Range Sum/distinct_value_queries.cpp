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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    map<int,set<int>> myMap;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        myMap[v[i]].insert(i);
    }
    map<int,vector<int>> oc;
    for (int i = 0; i < n; i++) {
        if (myMap[v[i]].upper_bound(i) == myMap[v[i]].end()) {
            v[i] = n;
        } else {
            v[i] = *myMap[v[i]].upper_bound(i);
        }
        oc[v[i]].push_back(i);
    }
    map<int,vector<pair<int,int>>> queries;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        queries[b].push_back({a, i});
    }
    segmentTree st;
    st.resz(n + 10);
    int ans[q];
    for (int i = n; i >= 0; i--) {
        for (auto& p: queries[i]) {
            ans[p.second] = st.query(p.first, i);
        }
        for (auto &j: oc[i]) {
            st.update(j, 1);
        }
    }
    for (int i: ans) {
        cout << i << "\n";
    }
}
