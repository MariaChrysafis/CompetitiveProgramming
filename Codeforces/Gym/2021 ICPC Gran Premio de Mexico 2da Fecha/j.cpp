#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>
#define ll long long

using namespace std;

struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return max(a,b);
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
            val[cur] = op(op(query(curX, x - 1), query(x + 1, curY)), y);
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

bool cust(pair<pair<int,int>,int> p1, pair<pair<int,int>,int> p2) {
    return (p1.first.second < p2.first.second);
}


void solve() {
    segmentTree st;
    st.resz((int)1e6 + 10);
    int A, T;
    cin >> A >> T;
    vector<pair<pair<int,int>,int>> vec;
    for(int i = 0; i < A; i++) {
        int h, d, t;
        cin >> h >> d >> t;
        for(int j = 0; j < t; j++) {
            int s;
            cin >> s;
            if(s <= T) {
                vec.push_back({{s, s + d - 1}, h});
                st.update(s + d, max(h, (int)st.query(s + d, s + d)));
            }
        }
    }
    sort(vec.begin(), vec.end()); //sort by endpoints
    for(pair<pair<int,int>,int> p: vec) {
        int start = p.first.first;
        int end = p.first.second;
        int happiness = p.second;
        int cur = st.query(end, end);
        if(start != 0) st.update(end, max((int)st.query(0, start - 1) + happiness, cur));
    }
    cout << st.query(0, (int)1e6) << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
