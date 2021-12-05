#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cstdint>
#include <cassert>
#include <bit>
#include <bitset>
#include <map>
#include <list>
#include <stack>
#include <algorithm>

#pragma GCC optimize("O1")
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")
#define ll long long
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, m, k;
    cin >> n >> m >> k;
    ll arr[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    map<ll,ll> dp1[n][m], dp2[n][m];
    for (int sz = 0; sz < 20; sz++) {
        for (int i = 0; i < (1 << sz); i++) {
            pair<int, int> loc = {0, 0};
            ll val = arr[0][0];
            bool fine = true;
            for (int j = 0; j < sz; j++) {
                if (i & (1 << j)) {
                    loc.first++;
                    if (loc.first == n) {
                        fine = false;
                        break;
                    }
                    val ^= arr[loc.first][loc.second];
                } else {
                    loc.second++;
                    if (loc.second == m) {
                        fine = false;
                        break;
                    }
                    val ^= arr[loc.first][loc.second];
                }
            }
            if (!fine) {
                continue;
            }
            dp1[loc.first][loc.second][val]++;
        }
    }
    for (int sz = 0; sz < 20; sz++) {
        for (int i = 0; i < (1 << sz); i++) {
            pair<int, int> loc = {n - 1, m - 1};
            ll val = arr[n - 1][m - 1];
            bool fine = true;
            for (int j = 0; j < sz; j++) {
                if (i & (1 << j)) {
                    loc.first--;
                    if (loc.first == -1) {
                        fine = false;
                        break;
                    }
                    val ^= arr[loc.first][loc.second];
                } else {
                    loc.second--;
                    if (loc.second == -1) {
                        fine = false;
                        break;
                    }
                    val ^= arr[loc.first][loc.second];
                }
            }
            if (!fine) {
                continue;
            }
            dp2[loc.first][loc.second][val]++;
        }
    }
    //cout << dp1[10][10][1] << '\n';

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + j == (n + m - 2)/2) {
                for (auto &p: dp1[i][j]) {
                    ans += p.second * dp2[i][j][k ^ p.first ^ arr[i][j]];
                }
            }
        }
    }
    cout << ans << '\n';
}
