#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

long long MOD = 998244353;

long long binPow(long long a) {
    long long ans = 1;
    long long ret = 2;
    while (a > 0) {
        if (a & 1) {
            ans *= ret, ans %= MOD;
        }
        a /= 2;
        ret *= ret, ret %= MOD;
    }
    return ans;
}

void solve() {
    int n, m;
    cin >> n >> m;
    int q;
    cin >> q;
    int emptyRows = n;
    int emptyCols = m;
    int badRows = 0;
    int badCols = 0;
    vector<vector<int>> inRow(n);
    vector<vector<int>> inCol(m);
    for (int i = 0; i < n; i++) inRow[i].resize(2);
    for (int i = 0; i < m; i++) inCol[i].resize(2);
    map<pair<int, int>, int> state;
    int hv[2] = {0, 0};
    auto updateRow = [&](int x, int sgn) {
        if (inRow[x][0] && inRow[x][1]) {
            badRows += sgn;
        } else if (!inRow[x][0] && !inRow[x][1]) {
            emptyRows += sgn;
        }
    };
    auto updateCol = [&](int y, int sgn) {
        if (inCol[y][0] && inCol[y][1]) {
            badCols += sgn;
        } else if (!inCol[y][0] && !inCol[y][1]) {
            emptyCols += sgn;
        }
    };
    auto remove = [&](int x, int y) {
        if (state[{x, y}] == 0) {
            return;
        }
        updateRow(x, -1);
        updateCol(y, -1);
        inRow[x][(x + y + state[{x, y}] + 1) % 2]--;
        inCol[y][(x + y + state[{x, y}] + 1) % 2]--;
        hv[(x + y + state[{x, y}] + 1) % 2]--;
        updateRow(x, 1);
        updateCol(y, 1);
        state[{x, y}] = 0;
    };
    auto add = [&](int x, int y, int z) {
        if (state[{x,y}] == z + 1) {
            return;
        }
        remove(x, y);
        updateRow(x, -1);
        updateCol(y, -1);
        inRow[x][(x + y + z) % 2]++;
        inCol[y][(x + y + z) % 2]++;
        hv[(x + y + z) % 2]++;
        updateRow(x, 1);
        updateCol(y, 1);
        state[{x, y}] = z + 1;
    };
    while (q--) {
        int x, y, val;
        cin >> x >> y >> val;
        x--, y--;
        if (val == -1) {
            remove(x, y);
            state[{x, y}] = 0;
        } else {
            add(x, y, val);
            state[{x, y}] = val + 1;
        }
        long long ans = 0;
        if (badRows == 0) {
            ans += binPow(emptyRows);
        }
        if (badCols == 0) {
            ans += binPow(emptyCols);
        }
        cout << (ans - !(bool) hv[0] - !(bool) hv[1] + MOD) % MOD << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
