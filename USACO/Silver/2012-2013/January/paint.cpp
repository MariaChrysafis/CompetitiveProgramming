#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <set>
#define ll int
using namespace std;
struct segmentTree {
    vector<ll> v;
    vector<ll> vec;
    vector<ll> addLater;

    void upd(int dum, int tl, int tr, int &l, int &r, ll val) {
        if (tr < l || tl > r) {
            return;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return;
        }
        ll mid = (tl + tr) >> 1;
        dum = dum << 1;
        upd(dum, tl, mid, l, r, val);
        upd(dum + 1, mid + 1, tr, l, r, val);
    }

    void upd(int l, int r, int val) {
        upd(1, 0, v.size() - 1, l, r, val);
    }

    ll get(int x) {
        int cur = x + v.size();
        ll ans = 0;
        while (true) {
            ans += addLater[cur];
            if (cur == 0) {
                break;
            }
            cur /= 2;
        }
        return ans;
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        vec.resize(v.size() * 2);
        addLater.resize(v.size() * 2);
    }

};
set<int> pos;
vector<int> set_to_vector(set<int> s) {
    vector<int> v;
    for (int i: s) {
        v.push_back(i);
    }
    return v;
}
int main() {
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    int curPos = 0;
    pos.insert(curPos);
    vector<int> positions = {0};
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        char c;
        cin >> c;
        if (c == 'L') {
            curPos -= x;
        } else {
            curPos += x;
        }
        pos.insert(curPos);
        positions.push_back(curPos);
    }
    map<int,int> old_new;
    int cntr = 0;
    for (int i: pos) {
        old_new[i] = cntr;
        cntr++;
    }
    segmentTree st;
    st.resz(positions.size() + 2);
    for (int i = 0; i < positions.size() - 1; i++) {
        int l = min(old_new[positions[i]], old_new[positions[i + 1]]);
        int r = max(old_new[positions[i]], old_new[positions[i + 1]]) - 1;
        st.upd(l, r, 1);
    }
    vector<int> v = set_to_vector(pos);
    int ans = 0;
    for (int i = 0; i < positions.size() - 1; i++) {
        if (st.get(i) >= k) {
            ans += abs(v[i] - v[i + 1]);
        }
    }
    cout << ans << endl;
}
