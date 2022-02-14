#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")

using namespace std;
vector<int> dif;
map<pair<int,int>,bool> dp;
bool dfs (int ind, int pref) {
    //cout << ind << " " << pref << '\n';
    if (dp.count({ind, pref})) {
        return dp[{ind, pref}];
    }
    if (ind == -1) {
        if (pref == 0) {
            return (dp[{ind, pref}] = true);
        }
        return (dp[{ind, pref}] = false);
    }
    if (dfs (ind - 1, pref - dif[ind])) {
        return dp[{ind, pref}] = true;
    }
    if (dfs (ind - 1, pref + dif[ind])) {
        return dp[{ind, pref}] = true;
    }
    return dp[{ind, pref}] = false;
}
void solve () {
    dif.clear(), dp.clear();
    int n; cin >> n;
    vector<int> a(n), b(n);
    int sum = 0;
    int sumsq = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        sumsq += a[i] * a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        sum += b[i];
        sumsq += b[i] * b[i];
    }
    for (int i = 0; i < n; i++) {
        dif.push_back(a[i] - b[i]);
    }
    int minDif = 1e9;
    for (int j = -100 * n; j <= 100 * n; j++) {
        if (dfs (n - 1, j)) {
            minDif = min(minDif, abs(j));
        }
    }
    int sa = (sum - minDif)/2;
    int sb = (sum + minDif)/2;
    cout << sa * sa + sb * sb + (n - 2) * sumsq << '\n';
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
