#include <vector>
#include <chrono>
#include <iostream>
#include <map>
#include <set>
#include <climits>
#include <cmath>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

using namespace std;

typedef long long ll;

struct Range_Query {
    vector<int> vec;
    vector<vector<int>> dp;
    int query (int l, int r) {
        int sz = (r - l + 1);
        sz = log2(sz);
        int left = dp[l][sz]; //l...l + 2^sz - 1
        int right = dp[r + 1 - (1 << sz)][sz]; //r - 2^sz + 1...r
        return max(left, right);
    }
    void update () {
        dp.resize(vec.size());
        for (int i = 0; i < vec.size(); i++) {
            dp[i].resize(32);
        }
        for (int j = 0; j < 32; j++) {
            for (int i = 0; i < vec.size(); i++) {
                if (j == 0) {
                    dp[i][j] = vec[i];
                    continue;
                }
                int nxt = i + (1 << (j - 1));
                dp[i][j] = dp[i][j - 1];
                if (nxt < vec.size()) {
                    dp[i][j] = max(dp[i][j], dp[nxt][j - 1]);
                }
            }
        }
    }
};

void solve () {
    int n;
    cin >> n;
    vector<int> p(n);
    Range_Query stma;
    int oc[n + 1];
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        oc[p[i]] = i;
    }
    stma.vec = p;
    stma.update();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        //binary search for the rightmost x for which rng_max[i...x] = p[i]
        int l = 0;
        int r = i;
        while (l != r) {
            int mid = (l + r )/2;
            if (stma.query(mid, i) == p[i]) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        int left = l;
        l = i;
        r = n - 1;
        while (l != r) {
            int mid = (l + r + 1)/2;
            //cout << l << " " << r << " " << mid << " " << stma.query(i, mid) << '\n';
            if (stma.query(i, mid) == p[i]) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        int right = r;
        pair<int,int> p1 = {left, i - 1};
        pair<int,int> p2 = {i + 1, right};
        if (p2.second - p2.first < p1.second - p1.first) {
            swap(p1, p2);
        }
        int cntr = 0;
        for (int ind = p1.first; ind <= p1.second; ind++) {
            if (oc[p[i] - p[ind]] >= p2.first && oc[p[i] - p[ind]] <= p2.second) {
                cntr++;
            }
        }
        ans += cntr;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
