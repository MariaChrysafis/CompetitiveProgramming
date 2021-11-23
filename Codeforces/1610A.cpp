#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <chrono>
#include <random>
#include <queue>
#include <cassert>
#include <map>
#include <algorithm>
#define ll int64_t
using namespace std;
vector<pair<int,int>> vec;
int dist (pair<int,int> p, pair<int,int> q) {
    return abs(p.first - q.first) + abs(p.second - q.second);
}
bool valid (int n, int m, vector<pair<int,int>> blocked) {
    vector<vector<int>> v(n * m);
    for (auto& p: blocked) {
        for (int i = 0; i < n * m; i++) {
            v[i].push_back(dist(vec[i], p));
        }
    }
    sort(v.begin(), v.end());
    for (int i = 1; i < n * m; i++) {
        if (v[i] == v[i - 1]) {
            return false;
        }
    }
    return true;
}
int bits (int x) {
    int cnt = 0;
    for (int i = 22; i >= 0; i--) {
        if (x & (1 << i)) {
            cnt++;
        }
    }
    return cnt;
}
void solver() {
    long long n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vec.push_back({i, j});
        }
    }
    int best = (1 << (n * m)) - 1;
    for (int i = 0; i < (1 << (n * m)); i++) {
        if (bits(i) > bits(best)) {
            continue;
        }
        vector<pair<int,int>> v;
        for (int j = 0; j < n * m; j++) {
            if (i & (1 << j)) {
                v.push_back(vec[j]);
            }
        }
        if (valid(n, m , v)) {
            cout << i << endl;
            best = i;
        }
    }
    cout << bits(best) << endl;
}
int solve () {
    long long n, m;
    cin >> n >> m;
    if (n == 1 && m == 1) {
        return 0;
    }
    if (n == 1 || m == 1) {
        return 1;
    }
    return 2;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        cout << solve() << '\n';
    }
}
