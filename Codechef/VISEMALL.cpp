#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;

struct segmentTree {
    vector<ll> vec;
    vector<ll> setLater;

    void push(int v, int tl, int tr) {
        if (setLater[v] % 2 == 0) {
            return;
        }
        int tm = (tl + tr)/2;
        setLater[2 * v + 1] += setLater[v];
        vec[2 * v + 1] = -vec[2 * v + 1] + (tr - tm);
        setLater[2 * v] += setLater[v];
        vec[2 * v] = -vec[2 * v] + (tm - tl + 1);
        setLater[v] = 0;
    }

    const ll INF = 0;

    ll upd(int dum, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            setLater[dum]++;
            return (vec[dum] = (tr - tl + 1) - vec[dum]);
        }
        push(dum, tl, tr);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r);
        upd(2 * dum + 1, mid + 1, tr, l, r);
        return (vec[dum] = vec[2 * dum] + vec[2 * dum + 1]);
    }

    void upd(int l, int r) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    ll get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum, tl, tr);
        int tm = (tl + tr) >> 1;
        return get(dum * 2, tl, tm, l, r) + get(dum * 2 + 1, tm + 1, tr, l, r);
    }

    ll get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    bool isAllZero (int l, int r) {
        return (get(l, r) == 0);
    }

    bool isAllOne (int l, int r) {
        if (r < l) return true;
        return (get(l, r) == r - l + 1);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.assign(sz * 2, 0);
        setLater.assign(sz * 2, 0);
    }

};
void solve() {
    int N, Q;
    cin >> N >> Q;
    string s;
    cin >> s;
    segmentTree st;
    st.resz(N);
    for (int i = 0; i < N; i++) {
        if (s[i] == '1') {
            st.upd(i, i);
        }
    }
    while (Q--) {
        int t;
        cin >> t;
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (t == 1) {
            st.upd(l, r);
        } else {
            int x;
            cin >> x;
            x--;
            if (st.isAllZero(l, r) || st.isAllOne(l, r)) {
                if (x == l) cout << "YES\n";
                else cout << "NO\n";
                continue;
            }
            //is there a division?
            int ones = st.get(l, r);
            if (st.get(r - ones + 1, r) == ones) {
                if (x == r - ones + 1) {
                    cout << "YES\n";
                    continue;
                }
                cout << "NO\n";
                continue;
            }
            if (st.get(l, l + ones - 1) == ones) {
                //111110000
                if (x == l + ones) {
                    cout << "YES\n";
                    continue;
                }
                cout << "NO\n";
                continue;
            }
            cout << "YES\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 1;
    while (t--) {
        solve();
    }
}
