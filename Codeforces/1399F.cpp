#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <map>
#include <algorithm>
#include <climits>
#include <cstring>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <cstring>

using namespace std;
typedef long long ll;
struct Solver {
    bool comp(pair<int, int> p1, pair<int, int> p2) {
        return (p1.second - p1.first < p2.second - p2.first);
    }

    int compress(vector<pair<int, int>> &v) {
        set<int> s;
        for (auto &p: v) {
            s.insert(p.first), s.insert(p.second);
        }
        map<int, int> myMap;
        int cntr = 1;
        for (int i: s) {
            myMap[i] = cntr++;
        }
        for (int i = 0; i < v.size(); i++) {
            v[i].first = myMap[v[i].first], v[i].second = myMap[v[i].second];
        }
        return cntr;
    }

    vector<vector<int>> dp;
    vector<vector<int>> endpnt;
    vector<pair<int, int>> vec;

    int memoize(int l, int r) {
        if (l > r) {
            return 0;
        }
        if (dp[l][r] != -1) {
            return dp[l][r];
        }
        dp[l][r] = max(memoize(l + 1, r), memoize(l, r - 1));
        int plus = 0;
        for (int i: endpnt[r]) {
            if (vec[i].first == l && vec[i].second == r) {
                plus = 1;
            } else if (vec[i].first >= l && vec[i].second == r) {
                dp[l][r] = max(dp[l][r], memoize(l, vec[i].first - 1) + memoize(vec[i].first, vec[i].second));
            }
        }
        return (dp[l][r] += plus);
    }

    void read() {
        int N;
        cin >> N;
        vec.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> vec[i].first >> vec[i].second;
        }
        int x = compress(vec);
        dp.resize(x), endpnt.resize(x);
        for (int i = 0; i < vec.size(); i++) {
            endpnt[vec[i].second].push_back(i);
        }
        for (int i = 0; i < x; i++) {
            dp[i].assign(x, -1);
        }
        cout << memoize(0, x - 1) << '\n';
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        Solver s;
        s.read();
    }
}
