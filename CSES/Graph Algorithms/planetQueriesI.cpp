#include <cmath>
#include <iostream>
#include <set>
#include <climits>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <type_traits>
#include <string>
#include <queue>
#define ll long long
#include <map>
 
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        v[i]--;
    }
    int dp[n][32];
    for (int j = 0; j < 32; j++) {
        for (int i = 0; i < n; i++) {
            if (j == 0) {
                dp[i][j] = v[i];
            } else {
                dp[i][j] = dp[dp[i][j - 1]][j - 1];
            }
        }
    }
    while (q--) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int i = 31; i >= 0; i--) {
            if (k & (1 << i)) {
                x = dp[x][i];
                k -= (1 << i);
            }
        }
        cout << ++x << '\n';
    }
 
}
