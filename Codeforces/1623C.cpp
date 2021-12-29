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

vector<int64_t> v, orig;

void print () {
    for (int i: v) {
        cout << i << ' ';
    }
    cout << '\n';
}

bool valid (int64_t min_num) {
    //reverse(v.begin(), v.end());
    v = orig;
    for (int i = v.size() - 1; i >= 2; i--) {
        if (v[i] < min_num) {
            return false;
        }
        int d = min(orig[i], v[i] - min_num)/3;
        v[i - 1] += d;
        v[i - 2] += 2 * d;
    }
    return (v[0] >= min_num && v[1] >= min_num);
}

void solve() {
    int N;
    cin >> N;
    v.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i];
    }
    orig = v;
    int64_t l = 0;
    int64_t r = 1e9;
    while (l != r) {
        int64_t m = (l + r + 1)/2;
        if (valid(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    assert(l == r);
    cout << l << '\n';

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
