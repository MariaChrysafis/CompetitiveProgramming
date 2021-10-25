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

#define ll long long
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    int MAX_5 = 5000;
    int dp[k + 1][MAX_5 + 1];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= MAX_5; j++) {
            dp[i][j] = -(int)1e9;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        int cntr2 = 0;
        int cntr5 = 0;
        while (x % 2 == 0) {
            x /= 2, cntr2++;
        }
        while (x % 5 == 0) {
            x /= 5, cntr5++;
        }
        for (int j = k; j >= 1; j--) {
            for (int v = MAX_5; v >= 0; v--) {
                if (v - cntr5 >= 0) {
                    dp[j][v] = max(dp[j][v], dp[j - 1][v - cntr5] + cntr2);
                }
            }
        }
    }
    int myMax = 0;
    for (int i = 0; i <= MAX_5; i++) {
        myMax = max(myMax, min(dp[k][i], i));
    }
    cout << myMax;
}
