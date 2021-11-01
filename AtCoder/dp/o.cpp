#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <queue>
#include <map>
#define ll signed long long
using namespace std;
const int MOD = 1e9 + 7;
int main() {
    int n;
    cin >> n;
    bool adj[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }
    long long prev[(1 << n)];
    long long cur[(1 << n)];
    for (int j = 0; j < (1 << n); j++) {
        prev[j] = cur[j] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (adj[0][i]) {
            prev[(1 << i)] = 1;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << n); j++) {
            if (!prev[j]) {
                continue;
            }
            for (int k = 0; k < n; k++) {
                if (!(j & (1 << k)) && adj[i][k]) {
                    cur[j + (1 << k)] += prev[j];
                    cur[j + (1 << k)] %= MOD;
                }
            }
        }
        for (int j = 0; j < (1 << n); j++) {
            prev[j] = cur[j];
            cur[j] = 0;
        }
    }
    cout << prev[(1 << n) - 1] << '\n';
}
