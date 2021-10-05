#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <chrono>

#include <queue>
#include <algorithm>
#include <cmath>
#include <fstream>

#pragma GCC optimize("O3")

#define ll long long
const int MOD = 1e9 + 7;
using namespace std;
struct Point {
    int x, y;
};
vector<Point> vec;
struct Triangle {
    int arr[3];
    int doubleArea() {
        int a = arr[0];
        int b = arr[1];
        int c = arr[2];
        return abs(vec[a].x * vec[b].y + vec[b].x * vec[c].y + vec[c].x * vec[a].y - vec[b].x * vec[a].y - vec[c].x * vec[b].y - vec[a].x * vec[c].y);
    }
    bool encapsulates(int p) {
        int a = arr[0];
        int b = arr[1];
        int c = arr[2];
        Triangle t1 = {{p, a, b}};
        Triangle t2 = {{p, b, c}};
        Triangle t3 = {{p, c, a}};
        return (t2.doubleArea() + t1.doubleArea() + t3.doubleArea() == doubleArea());
    }
};
bool comp(Triangle t1, Triangle t2) {
    return (t1.doubleArea() < t2.doubleArea());
}
int main() {
    int n;
    cin >> n;
    vec.resize(n);
    vector<Triangle> sorted;
    for (int i = 0; i < n; i++) {
        cin >> vec[i].x >> vec[i].y;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                sorted.push_back({{i, j, k}});
            }
        }
    }
    sort(sorted.begin(), sorted.end(), comp);
    long long dp[n + 1][n][n][n];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }
    for (Triangle t: sorted) {
        vector<int> inside;
        for (int i = 0; i < n; i++) {
            if (i == t.arr[0] || i == t.arr[1] || i == t.arr[2]) {
                continue;
            }
            if (t.encapsulates(i)) {
                inside.push_back(i);
            }
        }
        dp[t.arr[0]][t.arr[1]][t.arr[2]][0] = 1;
        for (int i = 1; i <= inside.size(); i++) {
            dp[t.arr[0]][t.arr[1]][t.arr[2]][i] += ((int)inside.size() - i + 1) * dp[t.arr[0]][t.arr[1]][t.arr[2]][i - 1];
            for (int j: inside) {
                vector<int> v1 = {t.arr[0], t.arr[1], j};
                sort(v1.begin(), v1.end());
                dp[t.arr[0]][t.arr[1]][t.arr[2]][i] += dp[v1[0]][v1[1]][v1[2]][i - 1];

                v1 = {t.arr[0], t.arr[2], j};
                sort(v1.begin(), v1.end());
                dp[t.arr[0]][t.arr[1]][t.arr[2]][i] += dp[v1[0]][v1[1]][v1[2]][i - 1];

                v1 = {t.arr[1], t.arr[2], j};
                sort(v1.begin(), v1.end());
                dp[t.arr[0]][t.arr[1]][t.arr[2]][i] += dp[v1[0]][v1[1]][v1[2]][i - 1];
            }
            dp[t.arr[0]][t.arr[1]][t.arr[2]][i] %= MOD;
        }
    }
    Triangle back = sorted.back();
    cout << (dp[back.arr[0]][back.arr[1]][back.arr[2]][n - 3] * 6) % MOD << endl;
}
