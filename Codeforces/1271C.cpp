#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <map>
using namespace std;
bool inside (int x1, int y1, int x2, int y2, int x, int y) {
    return (x >= min(x1, x2) && x <= max(x1, x2) && y >= min(y1, y2) && y <= max(y1, y2));
}
int solver (vector<pair<int,int>> vec, int sh_x, int sh_y, int s_x, int s_y) {
    int cntr = 0;
    for (auto &p: vec) {
        cntr += inside(p.first, p.second, s_x, s_y, sh_x, sh_y);
    }
    return cntr;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, sx, sy;
    cin >> n >> sx >> sy;
    vector<pair<int,int>> vec(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].first >> vec[i].second;
    }
    vector<pair<int,int>> pos;
    pair<int,int> ans;
    int best = -1;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (sx + dx < 0 || sy + dy < 0 || (dx == 0 && dy == 0)) {
                continue;
            }
            int x = solver(vec, sx + dx, sy + dy, sx, sy);
            if (x > best) {
                ans = {dx + sx, dy + sy};
                best = x;
            }
        }
    }
    cout << best << '\n';
    cout << ans.first << " " << ans.second << '\n';
}
