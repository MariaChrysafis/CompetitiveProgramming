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

vector<pair<int,int>> undo (int x, pair<int,int> p) {
    if (x == p.first) {
        p.first++;
        return {p};
    }
    if (x == p.second) {
        p.second--;
        return {p};
    }
    return {{p.first, x - 1}, {x + 1, p.second}};
}

void solve() {
    int N;
    cin >> N;
    vector<pair<int,int>> vec(N);
    vector<bool> vis;
    vis.assign(N, false);
    set<pair<int,int>> s;
    for (int i = 0; i < vec.size(); i++) {
        cin >> vec[i].first >> vec[i].second;
        s.insert(vec[i]);
    }
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i].first << " " << vec[i].second << ' ';
        for (int j = vec[i].first; j <= vec[i].second; j++) {
            bool fine = true;
            for (pair<int,int> p: undo(j, vec[i])) {
                if (!s.count(p)) {
                    fine = false;
                    break;
                }
            }
            if (fine) {
                cout << j << ' ';
                break;
            }
        }
        if (vec[i].first == vec[i].second) {
            cout << vec[i].first << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
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
