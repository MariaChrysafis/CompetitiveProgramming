#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;

void solve () {
    int N;
    cin >> N;
    for (int i = (1 << N) - 1; i < (1 << N); i++) {
        int grid[N][N];
        for (int x = 0; x < N; x++) {
            grid[0][x] = (bool)(i & (1 << x));
        }
        for (int x = 1; x < N; x++) {
            for (int y = 0; y < N; y++) {
                int ans = 1;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) == abs(dy)) continue;
                        if (x + dx - 1 < 0 || y + dy < 0) continue;
                        if (x + dx - 1 >= N || y + dy >= N) continue;
                        if ((vector<int>){x + dx - 1, y + dy} < (vector<int>){x, y}) {
                           ans ^= grid[x + dx - 1][y + dy];
                        }
                    }
                }
                grid[x][y] = ans;
            }
        }
        int arr[N][N];
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                cin >> arr[x][y];
            }
        }
        int ans = 0;
        for (int x = 0; x < N; x++) {
            for (int y = 0; y < N; y++) {
                //cout << grid[x][y];
                if (grid[x][y]) {
                    ans ^= arr[x][y];
                }
            }
            //cout << '\n';
        }
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    solve();
}
