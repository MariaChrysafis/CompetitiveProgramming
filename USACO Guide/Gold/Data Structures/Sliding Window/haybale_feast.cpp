#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <climits>
#include <vector>
#include <set>

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
        return max(query(dum, tl, mid, l, r), query(dum + 1, mid + 1, tr, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, (int)v.size() - 1, l, r);
    }

    void update(int x, ll y) {
        int cur = (int) v.size() + x;
        int curX = x;
        int curY = x;
        while (true) {
            val[cur] = max(max(query(curX, x - 1), query(x + 1, curY)), y);
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
vector<ll> pref = {0};
ll interval(int l, int r) {
    return pref[r + 1] - pref[l];
}
int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N, M;
    cin >> N >> M;
    segmentTree st;
    st.resz(N + 1);
    pair<ll, ll> vec[N];
    for (int i = 0; i < N; i++) {
        cin >> vec[i].first >> vec[i].second;
        pref.push_back(pref.back() + vec[i].first);
        st.update(i, vec[i].second);
    }
    ll myMin = LLONG_MAX;
    for (int i = 0; i < N; i++) {
        if (interval(i, N - 1) < M) {
            break;
        }
        int l = i;
        int r = N - 1;
        while (l < r) {
            int mid = (l + r)/2;
            if (interval(i, mid) >= M) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        myMin = min(myMin, st.query(i, l));
    }
    cout << myMin << endl;
}
