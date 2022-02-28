#include <cmath>
#include <cassert>
#include <iostream>
#include <set>
#include <climits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <type_traits>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
typedef long long ll;
vector<int64_t> dp;
vector<int64_t> last_pos;
int lcp (string s, string t) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != t[i]) {
            return i;
        }
    }
    return s.length();
}
int64_t solve (string s, vector<int64_t> pos, int lcp) {
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < pos.size(); j++) {
            if (pos[i] & (1 << j)) {
                if (s[j] != s[i]) {
                    pos[i] ^= (1 << j);
                }
            }
        }
    }
    lcp = 0;
    for (int i = 0; i < pos.size(); i++) {
        if (pos[i] != last_pos[i]) {
            lcp = i;
            break;
        }
    }
    dp[0] = 1;
    for (int i = (1 << lcp); i < dp.size(); i++) {
        int ind = __builtin_popcount(i) - 1;
        if (ind < lcp) {
            continue;
        }
        dp[i] = 0;
        int cur = pos[ind] & i;
        while (cur != 0) {
            int bt = cur & (-cur);
            dp[i] += dp[i - bt];
            cur -= bt;
        }
    }
    swap(last_pos, pos);
    return dp.back();
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    last_pos.assign(n, -1);
    dp.resize((1 << n));
    vector<vector<int64_t>> v(n);
    vector<int64_t> pos(n);
    for (int i = 0; i < n; i++) {
        pos[i] = 0;
        vector<int64_t> vec(n);
        for (int j = 0; j < vec.size(); j++) {
            cin >> vec[j];
            vec[j]--;
        }
        v[i] = vec;
        for (int j: vec) {
            pos[i] += (1 << j);
            if (j == i) {
                break;
            }
        }
    }
    vector<pair<string,int>> queries;
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        string s; cin >> s;
        if (s[0] == 'H') {
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == 'H') s[i] = 'G';
                else s[i] = 'H';
            }
        }
        queries.emplace_back(s, q);
    }
    sort(queries.begin(), queries.end());
    int64_t ans[Q];
    for (int q = 0; q < Q; q++) {
        if (q == 0) {
            ans[queries[q].second] = solve(queries[q].first, pos, -1);
        } else {
            ans[queries[q].second] = solve(queries[q].first, pos, lcp(queries[q].first, queries[q - 1].first));
        }
    }
    for (int64_t i: ans) {
        cout << i << '\n';
    }
}
