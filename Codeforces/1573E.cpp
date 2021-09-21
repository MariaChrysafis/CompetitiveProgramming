#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

const int INF = 1e9;

vector<vector<int>> dp;
vector<int> v;
map<int, vector<int>> oc;

int memoize(int i, int j) {
    if (i == j) {
        return (dp[i][j] = 0);
    }
    if (j - i == 1) {
        return (dp[i][j] = 1);
    }
    if (dp[i][j] != INF) {
        return dp[i][j];
    }
    int ans = memoize(i + 1, j) + 1;
    for (int x: oc[v[i]]) {
        if (x >= i + 1 && x <= j) {
            ans = min(memoize(i, x - 1) + memoize(x, j), ans);
        }
    }
    return (dp[i][j] = ans);
};

void solve() {
    oc.clear();
    int n;
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    vector<int> vec;
    int prev = -1;
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != prev) {
            vec.push_back(v[i]);
        }
        prev = v[i];
    }
    v = vec;
    for (int i = 0; i < v.size(); i++) {
        oc[v[i]].push_back(i);
    }
    dp.resize(n);
    for (int i = 0; i < n; i++) {
        dp[i].resize(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }

    cout << memoize(0, v.size() - 1) << endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
