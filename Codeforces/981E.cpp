#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

struct Possibilities {
    vector<ll> dp;
    vector<bool> pos;
    const int MOD = 23129189;
    int n;

    void resz (int N) {
        n = N;
        dp.assign(n, false);
        pos.assign(n, false);
        dp[0] = 1;
    }

    void update () {
        for (int i = 0; i < dp.size(); i++) {
            if (dp[i] >= 1) {
                pos[i] = true;
            }
        }
    }

    void add (int x) {
        for (int i = dp.size() - 1; i >= x; i--) {
            dp[i] += dp[i - x];
            dp[i] %= MOD;
        }
    }

    void remove (int x) {
        for (int i = x; i < dp.size(); i++) {
            dp[i] -= dp[i - x];
            dp[i] += MOD, dp[i] %= MOD;
        }
    }

    void print () {
        for (int i: pos) {
            cout << i << ' ';
        }
        cout << '\n';
    }
};

struct Query {
    int l, r, x;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    vector<vector<Query>> st(N), en(N);
    for (int i = 0; i < Q; i++) {
        Query qry;
        cin >> qry.l >> qry.r >> qry.x;
        qry.l--, qry.r--;
        st[qry.l].push_back(qry), en[qry.r].push_back(qry);
    }
    Possibilities ps;
    ps.resz((int)N + 1);
    for (int i = 0; i < N; i++) {
        //add all of the ones that started
        for (Query qry: st[i]) {
            ps.add(qry.x);
        }
        ps.update();
        if (i != 0) {
            for (Query qry: en[i - 1]) {
                ps.remove(qry.x);
            }
        }
    }
    vector<int> ans;
    for (int i = 1; i < ps.pos.size(); i++) {
        if (ps.pos[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << '\n';
    for (int i: ans) {
        cout << i << ' ';
    }
    cout << '\n';
}
