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
struct coord {
    ll x, y;
};
ll dist (coord a, coord b) {
    int d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    return d;
}
ll INF = 2e12;
int main() {
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int H, G;
    cin >> H >> G;
    vector<coord> holstein, guernsey;
    holstein.resize(H), guernsey.resize(G);
    for (int i = 0; i < H; i++) {
        cin >> holstein[i].x >> holstein[i].y;
    }
    for (int i = 0; i < G; i++) {
        cin >> guernsey[i].x >> guernsey[i].y;
    }
    ll dp[H + 1][G + 1][2]; //dp[i][j] --> we include i holsteins and j guernseys
    for (int i = 0; i <= H; i++) {
        for (int j = 0; j <= G; j++) {
            if (i == 0 && j == 0) {
                dp[i][j][0] = dp[i][j][1] = 0;
                continue;
            }
            if (i == 0) {
                dp[i][j][0] = dp[i][j][1] = INF;
                continue;
            }
            if (i == 1 && j == 0) {
                dp[i][j][0] = 0;
                dp[i][j][1] = INF;
                continue;
            }
            if (j == 0) {
                dp[i][j][0] = dp[i - 1][j][0] + dist(holstein[i - 1], holstein[i - 2]);
                dp[i][j][1] = INF;
                continue;
            }
            dp[i][j][0] = INF;
            dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][1] + dist(holstein[i - 1], guernsey[j - 1]));
            if (i >= 2) dp[i][j][0] = min(dp[i][j][0], dp[i - 1][j][0] + dist(holstein[i - 1], holstein[i - 2]));
            dp[i][j][1] = INF;
            if (j >= 2) dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][1] + dist(guernsey[j - 1], guernsey[j - 2]));
            dp[i][j][1] = min(dp[i][j][1], dp[i][j - 1][0] + dist(holstein[i - 1], guernsey[j - 1]));
        }
    }
    cout << dp[H][G][0] << '\n';
}
