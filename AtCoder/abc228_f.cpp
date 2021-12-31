#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <algorithm>
#include <set>
#include <cmath>
#include <cassert>
#include <map>

using namespace std;

typedef int64_t ll;

void print (vector<vector<ll>> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << ' ';
        }
        cout << '\n';
    }
}

struct Grid {
    vector<vector<ll>> grid;
    vector<vector<ll>> sums;
    ll find_sum (int l1, int r1, int l2, int r2) {
        return sums[l2 + 1][r2 + 1] - sums[l2 + 1][r1] - sums[l1][r2 + 1] + sums[l1][r1];
    }
    void fill () {
        sums.resize(grid.size() + 1);
        for (int i = 0; i < sums.size(); i++) {
            sums[i].resize(grid[0].size() + 1);
        }
        sums[0][0] = 0;
        for (int i = 1; i < sums.size(); i++) {
            sums[i][0] = 0;
        }
        for (int i = 1; i < sums[0].size(); i++) {
            sums[0][i] = 0;
        }
        for (int i = 1; i < sums.size(); i++) {
            for (int j = 1; j < sums[0].size(); j++) {
                sums[i][j] = sums[i][j - 1] + sums[i - 1][j] - sums[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }
    }
    void resz (int n, int m) {
        grid.resize(n);
        for (int i = 0; i < n; i++) {
            grid[i].resize(m);
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int H, W;
    cin >> H >> W;
    Grid g;
    g.resz(H, W);
    int h1, w1, h2, w2;
    cin >> h1 >> w1 >> h2 >> w2;
    h2 = min(h2, h1); w2 = min(w2, w1);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> g.grid[i][j];
        }
    }
    g.fill();
    //print(g.sums);
    //[0...H - h_1] and [0...W - w_1]
    ll sum_box[H - h2 + 1][W - w2 + 1];
    for (int i = 0; i <= H - h2; i++) {
        for (int j = 0; j <= W - w2; j++) {
            sum_box[i][j] = g.find_sum(i, j, i + h2 - 1, j + w2 - 1);
        }
    }
    ll ans = 0;
    for (int i = 0; i <= H - h1; i++) {
        multiset<ll> ms;
        for (int j1 = 0; j1 <= w1 - w2; j1++) {
            ll mm = 0;
            for (int i1 = i; i1 <= i + h1 - h2; i1++) {
                //ms.insert(sum_box[i1][j1]);
                mm = max(mm, sum_box[i1][j1]);
            }
            ms.insert(mm);
        }
        for (int j = 0; j <= W - w1; j++) {
            //[i, j] to [i + h1 - 1, j + w1 - 1]
            ll big = g.find_sum(i, j, i + h1 - 1, j + w1 - 1);
            auto it = ms.end();
            it--;
            ll myMax = *it;
            ll mm = 0;
            for (int i1 = i; i1 <= i + h1 - h2; i1++) {
                mm = max(mm, sum_box[i1][j]);
            }
            ms.erase(ms.find(mm));
            if (j != W - w1) {
                ll m = 0;
                for (int i1 = i; i1 <= i + h1 - h2; i1++) {
                    m = max(m, sum_box[i1][j + 1 + w1 - w2]);
                }
                ms.insert(m);
            }
            ans = max(ans, big - myMax);
        }
    }
    cout << ans;

}
