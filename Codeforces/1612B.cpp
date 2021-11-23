#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll __int128
using namespace std;
void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a == b) {
        cout << "-1\n";
        return;
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        if (i != a && i != b) {
            v.push_back(i);
        }
    }
    sort(v.begin(), v.end());
    reverse(v.begin(), v.end());
    vector<int> ans(n + 1);
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = -1;
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1 || i == n) continue;
        ans[i] = v[cnt];
        cnt++;
    }
    cnt = 0;
    for (int i = 1 ; i <= n; i++) {
        if (ans[i] == -1) {
            if (cnt == 0) ans[i] = a, cnt++;
            else ans[i] = b;
        }
    }
    int myMin = (int)1e8;
    for (int i = 1; i <= n/2; i++) {
        myMin = min(myMin, ans[i]);
    }
    int myMax = 0;
    for (int i = n/2 + 1; i <= n; i++) {
        myMax = max(myMax, ans[i]);
    }
    if (myMax == b && myMin == a) {
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    } else {
        cout << -1 << '\n';
    }
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
