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
const int MOD = 1e9 + 7;
int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    char arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    ll prev[n][n];
    ll cur[n][n];
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            prev[j][k] = cur[j][k] = 0;
        }
    }
    prev[0][0] = 1;
    cur[0][0] = 1;
    for (int len = 1; len < n; len++) {
        for (int i = 0; i < n; i++) { //how many moves we made left
            for (int j = 0; j < n; j++) { //how many moves we made right
                cur[i][j] = 0;
                int x1 = i; int y1 = len - i;
                int x2 = n - 1 - j; int y2 = n - 1 - len + j;
                if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) continue;
                //(0,0) --> (i, len - i)
                //(n-1,n-1) --> (n - 1 - j, n - 1 - len + j)
                if (arr[x1][y1] != arr[x2][y2]) {
                    continue;
                }
                if (i != 0 && j != 0) cur[i][j] += prev[i - 1][j - 1];
                if (j != 0) cur[i][j] += prev[i][j - 1];
                if (i != 0) cur[i][j] += prev[i - 1][j];
                cur[i][j] += prev[i][j];
                cur[i][j] %= MOD;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                prev[i][j] = cur[i][j];
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += prev[i][n - 1 - i];
        ans %= MOD;
    }
    cout << ans;
}
