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
    vector<int> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        s.push_back(v[i]);
    }
    vector<pair<char, pair<int,int>>> queries;
    while (q--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        if (c == '!') {
            s.push_back(y);
        } else {
            s.push_back(x), s.push_back(y);
        }
        queries.push_back(make_pair(c, make_pair(x,y)));
    }
    unordered_map<int,int> myMap;
    myMap.reserve(1000);
    sort(s.begin(), s.end());
    int cntr = 0;
    for (auto& i: s) {
        myMap[i] = cntr++;
    }
    for (int i = 0; i < n; i++) {
        v[i] = myMap[v[i]];
    }
    for (int i = 0; i < queries.size(); i++) {
        if (queries[i].first == '?') {
            queries[i].second.first = myMap[queries[i].second.first];
        }
        queries[i].second.second = myMap[queries[i].second.second];
    }
    segmentTree st;
    st.resz(s.size() + 1);
    for (int i = 0; i < n; i++) {
        st.update(v[i], 1);
    }
    for (auto& p: queries) {
        if (p.first == '!') {
            p.second.first--;
            st.update(v[p.second.first], -1);
            v[p.second.first] = p.second.second;
            st.update(v[p.second.first], 1);
        } else {
            cout << st.query(p.second.first, p.second.second) << '\n';
        }
    }
}
