#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
#include <set>

#define ll int

using namespace std;

struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 0;

    ll op(ll a, ll b) {
        return max(a,b);
    }

    ll query(int dum, int tl, int tr, int &l, int &r) {
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
        return query(1, 0, (int) v.size() - 1, l, r);
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
            if (cur % 2 == 0) {
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
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    segmentTree st;
    st.resz(n + 1);
    vector<int> v(n);
    map<int, int> oc;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        oc[v[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        v[i] = oc[v[i]];
    }
    int l = 0;
    int r = 0;
    int cntr = 1;
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) cnt[i] = 0;
    cnt[v[0]] = 1;
    int myMax = 0;
    while (l <= r && r != n - 1) {
        if (cntr + !cnt[v[r + 1]] > k + 1) {
            cnt[v[l]]--;
            if (cnt[v[l]] == 0) {
                cntr--;
            }
            st.update(v[l], cnt[v[l]]);
            l++;
        } else {
            cnt[v[r + 1]]++;
            if (cnt[v[r + 1]] == 1) {
                cntr++;
            }
            st.update(v[r + 1], cnt[v[r + 1]]);
            r++;
        }
        myMax = max(myMax, st.query(0, n - 1));
    }
    cout << myMax << endl;
}
