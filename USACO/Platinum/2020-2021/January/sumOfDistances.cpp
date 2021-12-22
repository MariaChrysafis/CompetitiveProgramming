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

struct Structure {
    int distance;
    int parity;
    int graph_number;
};

bool comp(Structure s1, Structure s2) {
    if (s1.distance != s2.distance) {
        return (s1.distance < s2.distance);
    }
    if (s1.graph_number != s2.graph_number) {
        return (s1.graph_number < s2.graph_number);
    }
    return (s1.parity < s2.parity);
}

vector<vector<int>> adj[(int) 4e5];
vector<vector<int>> dist[(int) 4e5];

ll compute(vector<Structure> vec, int T) {
    sort(vec.begin(), vec.end(), comp);
    ll res = 0;
    segmentTree st;
    st.resz(T);
    vector<int> cnt;
    cnt.assign(T, false);
    for (int ind = 0; ind < vec.size(); ind++) {
        auto q1 = vec[ind];
        if (q1.distance == 1e9) continue;
        cnt[q1.graph_number]++;
        st.update(q1.graph_number, cnt[q1.graph_number]);
        res += mult(mult(st.query(0, T - 1), inv(cnt[q1.graph_number])), q1.distance);
        res %= MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    vector<Structure> vecE, vecO, vec;
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
            dist[t][i].resize(2);
            dist[t][i][0] = dist[t][i][1] = 1e9;
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
            vecE.push_back((Structure) {dist[t][i][0], 0, t});
        }
        for (int i = 0; i < n; i++) {
            vecO.push_back((Structure) {dist[t][i][1], 1, t});
            vec.push_back((Structure) {max(dist[t][i][1], dist[t][i][0]), 1, t});
        }
    }
    cout << (compute(vecO, T) + compute(vecE, T) - compute(vec, T) + MOD) % MOD << '\n';
}
