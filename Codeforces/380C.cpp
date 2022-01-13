#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD = 1e9 + 7;

struct RMQ {
    vector<int> val;
    vector<vector<int>> bit;
    int query (int l, int r) {
        int sz = (r - l + 1);
        int lg2sz = log2(sz);
        int x1 = bit[l][lg2sz];
        int x2 = bit[r - (1 << lg2sz) + 1][lg2sz];
        return min(x1, x2);
    }
    void parse () {
        bit.resize(val.size());
        for (int i = 0; i < val.size(); i++) {
            bit[i].resize(32);
        }
        for (int j = 0; j < 32; j++) {
            for (int i = 0; i < val.size(); i++) {
                if (j == 0) {
                    bit[i][j] = val[i];
                    continue;
                }
                if (i + (1 << (j - 1)) >= val.size()) bit[i][j] = bit[i][j - 1];
                else bit[i][j] = min(bit[i][j - 1], bit[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
};

int extract (char c) {
    return ((c == '(') ? 1 : -1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    int pref = 0;
    vector<int> prefix_sums = {0};
    for (int i = 0; i < s.length(); i++) {
        pref += extract(s[i]);
        prefix_sums.push_back(pref);
    }
    RMQ rmq;
    rmq.val = prefix_sums;
    rmq.parse();
    int Q;
    cin >> Q;
    while (Q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int min_depth = rmq.query(l + 1, r + 1) - prefix_sums[l];
        min_depth = max(-min_depth, 0);
        int dif = prefix_sums[r + 1] - prefix_sums[l] + min_depth;
        cout << (r - l + 1) - min_depth - dif << '\n';
    }
}
