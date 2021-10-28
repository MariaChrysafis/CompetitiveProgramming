#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
using namespace std;
#define ll long long
int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    vector<vector<int>> ans(n + 1);
    for (int i = 0; i <= n; i++) {
        ans[i].resize(n + 1);
        for (int j = 0; j <= n; j++) {
            ans[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans[i][j] = max(ans[i - 1][j], ans[i][j - 1]);
            ans[i][j] = max(ans[i][j], ans[i - 1][j - 1] + (abs(a[i - 1] - b[j - 1]) <= 4));
        }
    }
    cout << ans[n][n];
}
