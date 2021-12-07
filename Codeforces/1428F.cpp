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

#define ll long long
using namespace std;
struct RMQ {
    vector<int> v;
    vector<vector<int>> dp;
    int query (int l, int r) {
        if (l == r) {
            return v[l];
        }
        int len = r - l + 1;
        return max(dp[l][log2(len)], dp[r - (1 << (int)log2(len)) + 1][log2(len)]);
    }
    void read() {
        dp.resize(v.size());
        for (int i = 0; i < v.size(); i++) {
            dp[i].resize(20);
        }
        for (int i = 0; i < v.size(); i++) {
            dp[i][0] = v[i];
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i < v.size(); i++) {
                dp[i][j] = max(dp[i][j - 1], dp[min(i + (1 << (j - 1)), (int)v.size() - 1)][j - 1]);
            }
        }
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> v1;
    v1.assign(n, 0);
    v1[0] = {s[0] - '0'};
    for (int i = 1; i < v1.size(); i++) {
        if (s[i] == '0') {
            v1[i] = 0;
        } else {
            v1[i] = v1[i - 1] + 1;
        }
    }
    vector<int> v2 = v1;
    vector<int> indMin, indMax;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] == 1) {
            indMin.push_back(i);
        }
        if (v1[i] != 0 && (i == v1.size() - 1 || v1[i + 1] == 0)) {
            indMax.push_back(i);
        }
    }
    for (int i = 0; i < indMin.size(); i++) {
        reverse(v2.begin() + indMin[i], v2.begin() + indMax[i] + 1);
    }
    RMQ rmq;
    v1.push_back(1e9);
    rmq.v = v1;
    v1.pop_back();
    rmq.read();
    vector<ll> cur(n);
    for (int i = 0; i < n; i++) {
        cur[i] = rmq.query(0, i);
    }
    ll val = 0;
    for (ll j: cur) val += j;
    ll ans = val;
    for (int i = 1; i < v2.size(); i++) {
        if (v2[i - 1] == 0) {
            ans += val;
            continue;
        }
        int l = i + v2[i];
        int r = v2.size();
        while (l != r) {
            int m = (l + r)/2;
            if (rmq.query(i + v2[i], m) >= v2[i - 1]) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        val -= (l - i + 1);
        ans += val;
    }
    cout << ans;

}
