#include <bits/stdc++.h>
using namespace std;
int main() {
    int H, W;
    cin >> H >> W;
    string arr[H];
    for (int i = 0; i < H; i++) {
        cin >> arr[i];
    }
    int64_t o[H][W + 1];
    for (int i = 0; i < H; i++) {
        o[i][0] = 0;
        for (int j = 0; j < W; j++) {
            o[i][j + 1] = o[i][j] + (arr[i][j] == 'O');
        }
    }
    int64_t x[W][H + 1];
    for (int i = 0; i < W; i++) {
        x[i][0] = 0;
        for (int j = 0; j < H; j++) {
            x[i][j + 1] = x[i][j] + (arr[j][i] == 'I');
        }
    }
    int64_t ans = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (arr[i][j] && x[j] && o[i]) {
                ans += (arr[i][j] == 'J') * (o[i][W] - o[i][j]) * (x[j][H] - x[j][i]);
            }
        }
    }
    cout << ans;
}
