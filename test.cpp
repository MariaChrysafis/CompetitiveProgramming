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
/*
void memoize(Triangle t, int inside) {
    for (int i = 0; i < vec.size(); i++) {
        if(i == t.arr[0] || i == t.arr[1] || i == t.arr[2]) {
            continue;
        }
        if(!t.encapsulates(i)) {
            cout << i << endl;
            Triangle myTriangle[3];
            myTriangle[0] = {{t.arr[1], t.arr[2], i}};
            myTriangle[1] = {{t.arr[0], t.arr[2], i}};
            myTriangle[2] = {{t.arr[0], t.arr[1], i}};
            for (int j = 0; j < 3; j++) {
                if(!myTriangle[j].encapsulates(i)) {
                    cout << t.arr[0] << " " << t.arr[1] << " " << t.arr[2] << " " << i << " " << t.arr[j] << endl;
                }
            }
            cout << endl;
        }
    }
}
 */
vector<vector<vector<int>>> pointsInside;
int memoize(Triangle t) {
    cout << t.arr[0] << " " << t.arr[1] << " " << t.arr[2] << endl;
    int ans = 3;
    for (int i = 0; i < pointsInside.size(); i++) {
        if (i == t.arr[0] || i == t.arr[1] || i == t.arr[2]) continue;
        if(t.encapsulates(i)) {
            Triangle t1 = {t.arr[0], t.arr[1], i};
            Triangle t2 = {t.arr[0], t.arr[2], i};
            Triangle t3 = {t.arr[1], t.arr[2], i};
            ans += memoize(t1) + memoize(t2) + memoize(t3) - 2;
        }
    }
    return (pointsInside[t.arr[0]][t.arr[1]][t.arr[2]] = ans);
}
int main() {
    int n;
    cin >> n;
    vec.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> vec[i].x >> vec[i].y;
    }
    pointsInside.resize(n);
    for (int i = 0; i < n; i++) {
        pointsInside[i].resize(n);
        for (int j = 0; j < n; j++) {
            pointsInside[i][j].resize(n);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if(i == j || j == k || i == k) continue;
                pointsInside[i][j][k] = memoize((Triangle){i, j, k});
                cout << i << " " << j << " " << k << " " << pointsInside[i][j][k] << endl;
            }
        }
    }
}
