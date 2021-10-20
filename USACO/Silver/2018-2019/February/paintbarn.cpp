#include <iostream>
#include <algorithm>
#include <cmath>
#define MAX_N 1000
using namespace std;
int grid[MAX_N][MAX_N];
void update (int x, int y, int val) {
    grid[x + 1][y + 1] += val;
}
void update(int x1, int y1, int x2, int y2) {
    update(x2, y2, 1), update(x1 - 1, y2, -1), update(x2, y1 - 1, -1), update(x1 - 1, y1 - 1, 1);
}
int main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, K;
    cin >> N >> K;
    int ans[MAX_N][MAX_N];
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            grid[i][j] = ans[i][j] = 0;
        }
    }
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        update(x1, y1, x2 - 1, y2 - 1);
    }

    for (int i = MAX_N - 2; i >= 0; i--) {
        for (int j = MAX_N - 2; j >= 0; j--) {
            ans[i][j] = ans[i + 1][j] + ans[i][j + 1] - ans[i + 1][j + 1] + grid[i + 1][j + 1];
        }
    }
    int cntr = 0;
    for (int i = 0; i < MAX_N - 2; i++) {
        for (int j = 0; j < MAX_N - 2; j++) {
            cntr += (ans[i][j] == K);
        }
    }
    cout << cntr << endl;
}
