#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <stack>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <string>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

const int MAX = 20;

int best (int x, int y) {
    if (x == -1) return y;
    if (y == -1) return x;
    return min(x, y);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;
    vector<int> arr(N);
    int IndexGreaterEqual[MAX][N];
    vector<vector<int>> mask(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        for (int j = 0; j < MAX; j++) {
            if (arr[i] & (1 << j)) {
                mask[i].push_back(j);
            }
        }
    }

    for (int i = 0; i < MAX; i++) {
        vector<int> v;
        for (int j = 0; j < N; j++) {
            if (arr[j] & (1 << i)) {
                v.push_back(j);
            }
        }
        for (int ind = 0; ind < N; ind++) {
            IndexGreaterEqual[i][ind] = -1;
        }
        for (int ind = 0; ind < v.size(); ind++) {
            int prev;
            if (ind == 0) prev = -1;
            else prev = v[ind - 1];
            for (int k = prev + 1; k <= v[ind]; k++) {
                IndexGreaterEqual[i][k] = v[ind];
            }
        }
    }
    //indexGreaterEqual[bit][ind] -> first thing after ind that contains a bit bit
    int dp[MAX][N];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    for (int j = N - 1; j >= 0; j--) {
        for (int i = MAX - 1; i >= 0; i--) {
            for (int bits: mask[j]) {
                if (bits == i) {
                    dp[i][j] = j;
                }
                if (j != N - 1 && IndexGreaterEqual[bits][j + 1] != -1) {
                    dp[i][j] = best(dp[i][j], dp[i][IndexGreaterEqual[bits][j + 1]]);
                }
            }
        }
    }
    while (Q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u == v) {
            cout << "Shi\n";
            continue;
        }
        int ans = -1;
        for (int i: mask[v]) {
            ans = best(ans, dp[i][u]);
        }
        cout << ((ans <= v && ans != -1) ? "Shi\n" : "Fou\n");
    }
}
