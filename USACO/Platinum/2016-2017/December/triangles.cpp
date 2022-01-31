#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <bitset>
#include <type_traits>
#include <string>
#include <queue>
#include <map>

using namespace std;
class Point {
public:
    int64_t x, y;
};
vector<Point> vec;
vector<vector<bitset<300>>> arr;
int64_t sgn (int i1, int i2, int i3) {
    return vec[i1].x * vec[i2].y - vec[i2].x * vec[i1].y + vec[i2].x * vec[i3].y - vec[i3].x * vec[i2].y + vec[i3].x * vec[i1].y - vec[i1].x * vec[i3].y;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);
    int N;
    cin >> N;
    vec.resize(N), arr.resize(N);
    for (int i = 0; i < N; i++) {
        arr[i].resize(N);
        cin >> vec[i].x >> vec[i].y;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (sgn(i, j, k) > 0) {
                    arr[i][j].set(k, true);
                }
            }
        }
    }
    int ans[N - 2];
    for (int i = 0; i < N - 2; i++) {
        ans[i] = 0;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = j + 1; k < N; k++) {
                if (sgn(i, j, k) > 0) {
                    ans[(arr[i][j] & arr[j][k] & arr[k][i]).count()]++;
                } else {
                    ans[(arr[j][i] & arr[i][k] & arr[k][j]).count()]++;
                }
            }
        }
    }
    for (int i: ans) {
        cout << i << '\n';
    }
}
