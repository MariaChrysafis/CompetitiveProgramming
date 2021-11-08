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
            cur >>= 1;
        }
    }

    void resz(int n) {
        v.resize((1 << (int) ceil(log2(n))));
        val.resize(v.size() * 2);
    }

};
ll solve (vector<int> v1, vector<int> v2) {
    int n = v1.size();
    map<int,int> myMap;
    for (int i = 0; i < n; i++) {
        v1[i]--;
        myMap[v1[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        v2[i]--;
        v2[i] = myMap[v2[i]];
    }
    segmentTree st;
    st.resz(n + 5);
    ll inversions = 0;
    for (int i = 0; i < n; i++) {
        inversions += st.query(v2[i] + 1, n - 1);
        st.update(v2[i], 1);
    }
    ll myMin = inversions;
    for (int i = 0; i < n; i++) {
        inversions += n - 1 - 2 * v2[i];
        myMin = min(myMin, inversions);
    }
    return myMin;
}
int main() {
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> v1(n), v2(n);
    for (int i = 0; i < n; i++) {
        cin >> v1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> v2[i];
    }
    cout << min(solve(v1, v2), solve(v2, v1));
}
