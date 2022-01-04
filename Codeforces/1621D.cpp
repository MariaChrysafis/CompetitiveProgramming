#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <queue>
#include <deque>
#include <cassert>
#include <map>
#include <iomanip>

using namespace std;

typedef int64_t ll;

int n;

int reduce (int x) {
    return (x = (x + 2 * n) % (2 * n));
}

void solve () {
    cin >> n;
    ll grid[2 * n][2 * n];
    ll init = 0;
    ll myMin = 1e10;
    set<int> s;
    s.insert({0, n - 1, n, 2 * n - 1});
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            cin >> grid[i][j];
            if (i >= n && j >= n) {
                init += grid[i][j];
                continue;
            }
            if (i < n && j < n) {
                init += grid[i][j];
                continue;
            }
            if (s.count(i) && s.count(j)) {
                myMin = min(myMin, grid[i][j]);
            }
        }
    }
    cout << init + myMin << '\n';
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
