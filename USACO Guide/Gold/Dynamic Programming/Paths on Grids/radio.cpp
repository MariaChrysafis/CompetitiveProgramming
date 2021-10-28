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
struct Coord {
    int x, y;
};
int dist (Coord c1, Coord c2) {
    return (c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y);
}
int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    Coord bessie, fj;
    cin >> bessie.x >> bessie.y;
    cin >> fj.x >> fj.y;
    string b, f;
    cin >> b >> f;
    vector<Coord> location_bessie = {bessie};
    vector<Coord> location_fj = {fj};
    for (int i = 0; i < n; i++) {
        Coord prev = location_bessie.back();
        if (b[i] == 'N') prev.y++;
        if (b[i] == 'S') prev.y--;
        if (b[i] == 'W') prev.x--;
        if (b[i] == 'E') prev.x++;
        location_bessie.push_back(prev);
    }
    for (int i = 0; i < m; i++) {
        Coord prev = location_fj.back();
        if (f[i] == 'N') prev.y++;
        if (f[i] == 'S') prev.y--;
        if (f[i] == 'W') prev.x--;
        if (f[i] == 'E') prev.x++;
        location_fj.push_back(prev);
    }
    ll dp[location_bessie.size()][location_fj.size()];
    for (int i = 0; i < location_bessie.size(); i++) {
        for (int j = 0; j < location_fj.size(); j++) {
            if (i == 0 && j == 0) {
                dp[0][0] = 0;
                continue;
            }
            dp[i][j] = INT_MAX;
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i][j - 1] + dist(location_bessie[i], location_fj[j]));
            if (i > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j] + dist(location_bessie[i], location_fj[j]));
            if (i > 0 && j > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + dist(location_bessie[i], location_fj[j]));
        }
    }
    cout << dp[location_bessie.size() - 1][location_fj.size() - 1];
}
