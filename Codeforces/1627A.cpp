#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

void solve () {
    int N, M, r, c;
    cin >> N >> M >> r >> c;
    r--, c--;
    vector<string> vec(N);
    for (int i = 0; i < N; i++) {
        cin >> vec[i];
    }
    int row = 0; int col = 0;
    for (int i = 0; i < N; i++) {
        if (vec[i][c] == 'B') {
            col++;
        }
    }
    for (int i = 0; i < M; i++) {
        if (vec[r][i] == 'B') {
            row++;
        }
    }
    bool black = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++ ){
            if (vec[i][j] == 'B') {
                black = true;
            }
        }
    }
    if (!black) {
        cout << "-1\n";
        return;
    }
    if (vec[r][c] == 'B') {
        cout << 0 << '\n';
    } else {
        if (row || col) {
            cout << 1 << '\n';
        } else {
            cout << 2 << '\n';
        }
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
