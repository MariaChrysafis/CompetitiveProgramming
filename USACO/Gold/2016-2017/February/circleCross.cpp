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
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v(2 * n);
    vector<vector<int>> vec(n);
    for (int i = 0; i < 2 * n; i++) {
        int x;
        cin >> x;
        x--;
        vec[x].push_back(i);
    }
    vector<pair<int,int>> intervals(n);
    for (int i = 0; i < n; i++) {
        intervals[i] = {vec[i][0], vec[i][1]};
    }
    sort(intervals.begin(), intervals.end());
    segmentTree st;
    ll ans = 0;
    st.resz(2 * n + 2);
    for (auto& p: intervals) {
        //cout << p.first << " " << p.second << '\n';
        ans += st.query(p.second + 1, 2 * n) + st.query(0, p.first - 1);
        st.update(p.first, 1);
        st.update(p.second, -1);
    }
    cout << ans;
}
