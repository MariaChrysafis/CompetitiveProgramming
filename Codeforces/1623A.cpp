#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <cmath>
#include <set>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <map>
#include <cassert>
#include <random>
using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

const int MOD = 1e9 + 7;

void solve() {
    int64_t n, m, rb, cb, rd, cd;
    cin >> n >> m >> rb >> cb >> rd >> cd;
    pair<int,int> cur = {rb, cb};
    pair<int,int> d = {1, 1};
    int time = 0;
    while (true) {
        if (cur.first + d.first == 0 || cur.first + d.first == n + 1) {
            d.first = -d.first;
        }
        if (cur.second + d.second == 0 || cur.second + d.second == m + 1) {
            d.second = -d.second;
        }
        time++;
        if (cur.first == rd || cur.second == cd) {
            cout << time - 1 << '\n';
            break;
        }
        cur.first += d.first, cur.second += d.second;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
