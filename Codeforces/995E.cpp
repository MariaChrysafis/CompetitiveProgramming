#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#pragma GCC optimization ("O1")
#pragma GCC optimization ("avx")
#pragma GCC optimize("unroll-loops")

using namespace std;
typedef long long ll;

ll MOD;

ll binPow (ll x, ll y) {
    ll ans = 1;
    ll res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}

ll inv (ll x) {
    return binPow(x, MOD - 2);
}

vector<ll> special;
vector<bool> hasVisited;

struct Query {
    ll current;
    ll previous;
    ll type;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll u, v;
    cin >> u >> v >> MOD;
    queue<Query> q[2];
    q[0].push({u, -1, -1}), q[1].push({v, -1, -1});
    map<int,int> prev[2];
    set<int> sp[2];
    int intermediate;
    while (true) {
        bool fine = false;
        for (int i = 0; i < 2; i++) {
            Query qry = q[i].front();
            q[i].pop();
            if (sp[i].count(qry.current)) {
                continue;
            }
            prev[i][qry.current] = qry.previous;
            sp[i].insert(qry.current);
            if (sp[!i].count(qry.current) != 0) {
                fine = true;
                intermediate = qry.current;
            }
            q[i].push({(qry.current + MOD - 1) % MOD, qry.current, 2});
            q[i].push({(qry.current + 1) % MOD, qry.current, 1});
            q[i].push({inv(qry.current), qry.current, 3});
        }
        if (fine) {
            break;
        }
    }
    vector<ll> ans;
    int cur = intermediate;
    ans.push_back(intermediate);
    while (cur != u) {
        cur = prev[0][cur];
        ans.push_back(cur);
    }
    reverse(ans.begin(), ans.end());
    cur = intermediate;
    while (cur != v) {
        cur = prev[1][cur];
        ans.push_back(cur);
    }
    cout << ans.size() - 1 << '\n';
    for (int i = 1; i < ans.size(); i++) {
        if (ans[i] == (ans[i - 1] + 1) % MOD) {
            cout << 1 << ' ';
        } else if (ans[i] == (ans[i - 1] - 1 + MOD) % MOD) {
            cout << 2 << ' ';
        } else {
            cout << 3 << ' ';
        }
    }

}
