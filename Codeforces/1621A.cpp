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

void solve () {
    int N, K;
    cin >> N >> K;
    char grid[N][N];
    int cntr = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = '.';
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j && i % 2 == 0) {
                if (cntr == K) {
                    break;
                }
                cntr++;
                grid[i][j] = 'R';
            }
        }
    }
    if (cntr != K) {
        cout << "-1\n";
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
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
