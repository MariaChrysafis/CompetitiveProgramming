#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O2")
#pragma GCC optimization ("unroll-loops")
#include <limits.h>
using namespace std;
 
int64_t binPow (int64_t x, int64_t y, int64_t MOD) {
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x, int64_t MOD) {
    return binPow(x, MOD - 2, MOD);
}
struct Hasher {
    void resz (int mod, int base, string str) {
        int n = str.size();
        this->sz = n;
        this->MOD = mod, this->BASE = base;
        this->pref.assign(n + 1, 0);
 
        for (int i = 1; i <= n; i++) {
            pref[i] = (BASE * pref[i - 1] + (str[i - 1] - 'A' + 1)) % MOD;
        }
    }
    int sz;
    int MOD;
    int BASE;
    vector<int64_t> pref;
    int64_t query (int l, int r) {
        return (pref[r + 1] - (binPow(BASE, r - l + 1, MOD)  * pref[l]) % MOD + MOD) % MOD;
    }
};
vector<int> dp;
vector<vector<int>> adj;
int myMax = 0;
void rec (int curNode) {
    if (dp[curNode] != 0) {
        return;
    }
    dp[curNode] = 0;
    for (int i: adj[curNode]) {
        rec(i);
        dp[curNode] = max(dp[curNode], dp[i]);
    }
    dp[curNode] ++;
    myMax = max(myMax, dp[curNode]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    unordered_map<int64_t,int> myMap;
    adj.resize(N);
    dp.assign(N, 0);
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        Hasher h1; h1.resz(1e9 + 9, 31, str);
        for (int l = 1; l <= str.size(); l++) {
            if (h1.query(0, l - 1) == h1.query(str.size() - l, str.size() - 1)) {
                if (myMap.count(h1.query(0, l - 1))) {
                    adj[i].push_back(myMap[h1.query(0, l - 1)]);
                }
            }
        }
        myMap[h1.query(0, str.size() - 1)] = i;
    }
    for (int i = 0; i < N; i++) {
        rec(i);
    }
    cout << myMax;
 
 
}
