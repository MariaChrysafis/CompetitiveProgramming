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

typedef long long ll;
const int MOD = 1e9 + 7;
using namespace std;

ll mult(ll x, ll y) {
    return (x * y) % MOD;
}

ll binPow(ll x, ll y) {
    ll res = x;
    ll ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res);
        y /= 2;
    }
    return ans;
}

ll inv(ll x) {
    return binPow(x, MOD - 2);
}

struct segmentTree {
    vector<ll> v;
    vector<ll> val;

    ll ID = 1;

    ll op(ll a, ll b) {
        return (a * b) % MOD;
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
        v.assign((1 << (int) ceil(log2(n))), 0);
        val.assign(v.size() * 2, 0);
    }

};

vector<vector<int>> adj[(int) 4e5];
vector<vector<int>> dist[(int) 4e5];

ll compute(vector<pair<int,int>> vec, int T) {
    sort(vec.begin(), vec.end());
    ll res = 0;
    segmentTree st;
    st.resz(T);
    vector<int> cnt;
    cnt.assign(T, false);
    for (auto& q1: vec) {
        if (q1.first == 1e9) {
            continue;
        }
        cnt[q1.second]++;
        st.update(q1.second, cnt[q1.second]);
        res += mult(mult(st.query(0, T - 1), inv(cnt[q1.second])), q1.first);
        res %= MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    vector<pair<int,int>> vecE, vecO, vec;
    for (int t = 0; t < T; t++) {
        int n, m;
        cin >> n >> m;
        adj[t].resize(n);
        while (m--) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[t][u].push_back(v), adj[t][v].push_back(u);
        }
        dist[t].resize(n);
        for (int i = 0; i < n; i++) {
            dist[t][i].assign(2, 1e9);
        }
        queue<pair<int, int>> q;
        q.push({0, 0});
        while (!q.empty()) {
            int curNode = q.front().second;
            int curDist = q.front().first;
            q.pop();
            if (dist[t][curNode][curDist % 2] != 1e9) {
                continue;
            }
            dist[t][curNode][curDist % 2] = curDist;
            for (int i: adj[t][curNode]) {
                q.push({curDist + 1, i});
            }
        }
        for (int i = 0; i < n; i++) {
            vecE.push_back( {dist[t][i][0], t});
            vecO.push_back( {dist[t][i][1], t});
            vec.push_back( {max(dist[t][i][1], dist[t][i][0]), t});
        }
    }
    cout << (compute(vecO, T) + compute(vecE, T) - compute(vec, T) + MOD) % MOD << '\n';


}
