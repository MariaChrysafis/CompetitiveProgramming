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
typedef long long ll;
void solve (string s, vector<int> pos) {
    for (int i = 0; i < pos.size(); i++) {
        for (int j = 0; j < pos.size(); j++) {
            if (pos[i] & (1 << j)) {
                if (s[j] != s[i]) {
                    pos[i] ^= (1 << j);
                }
            }
        }
    }
    vector<int> dp((1 << (int)pos.size()));
    dp[0] = 1;
    for (int i = 1; i < dp.size(); i++) {
        int ind = __builtin_popcount(i) - 1;
        dp[i] = 0;
        int cur = pos[ind] & i;
        while (cur != 0) {
            int bt = log2(cur);
            dp[i] += dp[i - (1 << bt)];
            cur -= (1 << bt);
        }
    }
    cout << dp.back() << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> v(n);
    vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[i] = 0;
        vector<int> vec(n);
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
    int Q;
    cin >> Q;
    while (Q--) {
        string s;
        cin >> s;
        solve(s, pos);
    }
}
