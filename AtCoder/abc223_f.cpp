#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;
struct segmentTree {
    vector<ll> vec;
    vector<ll> addLater;

    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const ll INF = 1e18;

    ll upd(int dum, int tl, int tr, int l, int r, ll val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        ll left = upd(2 * dum, tl, mid, l, r, val);
        ll right = upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = min(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return min(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }
};
int cost (char c) {
    if (c == '(') {
        return 1;
    } else {
        return -1;
    }
}
string s;
segmentTree st;
void update (int x, char c) {
    if (c == '(') {
        st.upd(x + 1, s.length(), 2);
    } else {
        st.upd(x + 1, s.length(), -2);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    st.resz(N);
    cin >> s;
    int pref = 0;
    for (int i = 0; i < N; i++) {
        st.upd(i + 1, i + 1, pref += cost(s[i]));
    }
    while (Q--) {
        int t;
        cin >> t;
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (t == 1) {
            if (s[l] == s[r]) {
                continue;
            }
            update(l, s[r]);
            update(r, s[l]);
            swap(s[l], s[r]);
        } else {
            if (st.get(l, l) != st.get(r + 1, r + 1)) {
                cout << "No\n";
                continue;
            }
            if (st.get(l + 1, r + 1) != st.get(l, l)) {
                cout << "No\n";
                continue;
            }
            cout << "Yes\n";
        }
    }
}
