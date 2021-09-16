#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

template<typename T>
T readVal() {
    T n;
    cin >> n;
    return n;
}

template<typename T>
vector<T> readVector(T n) {
    vector<T> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    return v;
}

template<typename T>
void printVector(vector<T> vec) {
    cout << "! ";
    for (T x: vec) {
        cout << x << " ";
    }
    cout << endl;
}

long long powr(long long x) {
    long long cur = 1;
    while (x--) {
        cur *= 2;
    }
    return cur;
}

void solve() {
    int n;
    cin >> n;
    long long arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i % 2 == 0) {
                arr[i][j] = 0;
            } else if (i == 1 && j == 0) {
                arr[i][j] = powr(53);
            } else if (i == 1) {
                arr[i][j] = arr[i][j - 1] / 2;
            } else {
                arr[i][j] = arr[i - 2][j] / 4;
            }
            cout << arr[i][j] << " ";
            cout.flush();
        }
        cout << endl;
        cout.flush();
    }

    int q;
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        int curX = 0;
        int curY = 0;
        while (curX != n - 1 || curY != n - 1) {
            cout << curX + 1 << " " << curY + 1 << endl;
            cout.flush();
            if (curX == n - 1) {
                curY++;
                continue;
            }
            if (curY == n - 1) {
                curX++;
                continue;
            }
            long long valDown = arr[curX + 1][curY];
            long long valRight = arr[curX][curY + 1];
            if (valDown) {
                if (k & valDown) curX++;
                else curY++;
            } else {
                if (k & valRight) curY++;
                else curX++;
            }
        }
        cout << n << " " << n << endl;
        cout.flush();
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
