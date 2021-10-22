#include <cmath>
#include <iostream>
#include <set>
#include <vector>
#include <map>
using namespace std;
#define ll long long
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
int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    ll N, K;
    cin >> N >> K;
    segmentTree st;
    vector<int> teams(N);
    st.resz(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> teams[i];
        st.update(i, teams[i]);
    }
    vector<ll> dp(N + 1);
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        if (i <= K) {
            dp[i] = st.query(0, i - 1) * i;
            continue;
        }
        dp[i] = 0;
        for (int len = 1; len <= K; len++) {
            dp[i] = max(dp[i - len] + st.query(i - len, i - 1) * len, dp[i]);
        }
    }
    cout << dp[N] << endl;
}
