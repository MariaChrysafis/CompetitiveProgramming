#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
using namespace std;
struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 1e9;

    ll op(ll a, ll b) {
        return min(a,b);
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

const int MAX = 2e5;
int dp[MAX][20];
int find (int curNode, int curDist) {
    if (curDist == 0) return curNode;
    if (curNode == -1) return -1;
    int lg2 = log2(curDist);
    return find(dp[curNode][lg2], curDist - (1 << lg2));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;
    int a[n];
    int nxtA[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; i++) {
        nxtA[a[i]] = a[(i + 1) % n];
    }
    int b[m];
    set<int> myMap[n];
    for (int i = 0; i < m; i++) {
        cin >> b[i]; b[i]--;
        myMap[b[i]].insert(i);
    }
    int nxt[m];
    for (int i = 0; i < m; i++) {
        nxt[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        auto it = myMap[nxtA[b[i]]].upper_bound(i);
        if (it == myMap[nxtA[b[i]]].end()) {
            continue;
        }
        nxt[i] = *it;
    }
    for (int j = 0; j < 20; j++) {
        for (int i = 0; i < m; i++) {
            if (j == 0) {
                dp[i][j] = nxt[i];
            } else {
                if (dp[i][j - 1] == -1) {
                    dp[i][j] = -1;
                    continue;
                }
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }
    int dp[n];
    segmentTree st;
    st.resz(m);
    for (int i = 0; i < m; i++) {
        dp[i] = find(i, n - 1);
        if (dp[i] == -1) {
            dp[i] = 1e9;
        }
        st.update(i, dp[i]);
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (st.query(l, m - 1) <= r) {
            cout << 1;
        } else {
            cout << 0;
        }
    }


}
