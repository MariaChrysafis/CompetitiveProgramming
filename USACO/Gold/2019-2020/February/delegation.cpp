#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <algorithm>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
int len;
vector<vector<int>> adj;
vector<int> cnt;

void clear(vector<int> spare) {
    for (int i = 0; i < spare.size(); i++) {
        cnt[spare[i]] = 0;
    }
}

int knapsack(vector<int> spare) {
    for (int i = 0; i < spare.size(); i++) {
        cnt[spare[i]]++;
    }
    for (int i = 0; i < spare.size(); i++) {
        if (spare[i] != 0) {
            if (spare[i] * 2 == len) {
                int x = cnt[spare[i]];
                cnt[spare[i]] -= x / 2 * 2;
            } else {
                int mn = min(cnt[spare[i]], cnt[len - spare[i]]);
                cnt[spare[i]] -= mn, cnt[len - spare[i]] -= mn;
            }
        }
    }
    int ans = 0;
    set<int> s;
    for (int i = 0; i < spare.size(); i++) {
        if (spare[i] != 0 && cnt[spare[i]] > 0) {
            s.insert(spare[i]);
        }
    }
    for (int i: s) {
        ans += cnt[i];
    }
    if (ans == 0) {
        clear(spare);
        return 0;
    }
    if (ans >= 2) {
        clear(spare);
        return -1;
    }
    for (int i: s) {
        if (cnt[i] > 0) {
            clear(spare);
            return i;
        }
    }
    return 0;
}

vector<int> dp;

int dfs(int x, int prev) {
    if (dp[x] != -2) {
        return dp[x];
    }
    if (x != 0 && adj[x].size() == 1) {
        return 0;
    }
    vector<int> spare = {};
    for (int i: adj[x]) {
        if (i != prev) {
            if (dfs(i, x) == -1) {
                return -1;
            }
            spare.push_back((dfs(i, x) + 1) % len);
        }
    }
    dp[x] = knapsack(spare);
    return dp[x];
}

int main() {
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    adj.resize(n);
    dp.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    map<int,bool> val;
    for (int i = 1; i <= n - 1; i++) {
        if ((n - 1) % i == 0) {
            cnt.resize(i);
            for (int j = 0; j < n; j++) {
                dp[j] = -2;
            }
            for (int j = 0; j < i; j++) {
                cnt[j] = 0;
            }
            len = i;
            bool b;
            if ((n - 1) % 3 == 0 && i % 3 == 0 && !val[i / 3]) {
              b = false;
            } else {
              b = (dfs(0, -1) != -1);
            }
            val[i] = b;
            cout << b;
        } else {
            cout << 0;
        }
    }
    return 0;
}
