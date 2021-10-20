#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    int arr[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    int ans[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0) {
                ans[i][j] = arr[i][j];
            } else if (i == 0) {
                ans[i][j] = ans[i][j - 1] + arr[i][j];
            } else if (j == 0) {
                ans[i][j] = ans[i - 1][j] + arr[i][j];
            } else {
                ans[i][j] = ans[i - 1][j] + ans[i][j - 1] - ans[i - 1][j - 1] + arr[i][j];
            }
        }
    }
    int myMax = -127;
    for (int x1 = 0; x1 < N; x1++) {
        for (int y1 = 0; y1 < N; y1++) {
            for (int x2 = x1; x2 < N; x2++) {
                for (int y2 = y1; y2 < N; y2++) {
                    int res;
                    if (x1 == 0 && y1 == 0) {
                        res = ans[x2][y2];
                    } else if (x1 == 0) {
                        res = ans[x2][y2] - ans[x2][y1 - 1];
                    } else if (y1 == 0) {
                        res = ans[x2][y2] - ans[x1 - 1][y2];
                    } else {
                        res = ans[x2][y2] + ans[x1 - 1][y1 - 1] - ans[x1 - 1][y2] - ans[x2][y1 - 1];
                    }
                    myMax = max(myMax, res);
                }
            }
        }
    }
    cout << myMax << endl;
}
