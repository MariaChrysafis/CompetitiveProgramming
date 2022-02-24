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
class SparseTable {
public:
    string s;
    vector<vector<int>> dp;
    int query (int l, int r) {
        int sz = log2(r - l + 1);
        return dp[l][sz] | dp[r - (1 << sz) + 1][sz];
    }
    SparseTable (string s) {
        this->s = s;
        dp.resize(s.size());
        for (int i = 0; i < dp.size(); i++) {
            dp[i].resize(32);
            dp[i][0] = (1 << (s[i] - 'a'));
        }
        for (int j = 1; j < 32; j++) {
            for (int i = 0; i < dp.size(); i++) {
                dp[i][j] = dp[i][j - 1] | dp[min(i + (1 << (j - 1)), (int)dp.size() - 1)][j - 1];
            }
        }
    }
};

class Hasher {
    vector<int64_t> pref = {0};
    const int MOD = 1e9 + 7;
    vector<int64_t> powr = {1};
    const int base = 2;
public:
    int64_t query (int l, int r) {
        return (pref[r + 1] - (pref[l] * powr[r - l + 1]) % MOD + MOD) % MOD;
    }
    void add (char c) {
        pref.push_back(pref.back() * base);
        pref.back() += (c - '0');
        pref.back() %= MOD;
        powr.push_back(powr.back() * base);
        powr.back() %= MOD;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, Q;
    cin >> N >> Q;
    string s;
    cin >> s;
    SparseTable sparseTable(s);
    vector<vector<int>> myMap(26);
    for (int i = 0; i < 26; i++) {
        myMap[i].resize(s.length());
        for (int j = 0; j < s.length(); j++) {
            if (s[j] - 'a' == i) {
                myMap[i][j] = j;
            } else {
                if (j != 0) myMap[i][j] = myMap[i][j - 1];
                else myMap[i][j] = -1;
            }
        }
    }
    Hasher v[26];
    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 0; i < s.length(); i++) {
            if (c == s[i]) v[c - 'a'].add('1');
            else v[c - 'a'].add('0');
        }
    }
    vector<int> new_map;
    while (Q--) {
        int x, y, len;
        cin >> x >> y >> len;
        x--, y--;
        if (__builtin_popcount(sparseTable.query(x, x + len - 1)) != __builtin_popcount(sparseTable.query(y, y + len - 1))) {
            cout << "NO\n";
            continue;
        }
        new_map.assign(26, -1);
        for (int i = 0; i < 26; i++) {
            if (sparseTable.query(x, x + len - 1) & (1 << i)) {
                int firstOc = myMap[i][x + len - 1];
                new_map[s[firstOc] - 'a'] = s[y - x + firstOc] - 'a';
            }
        }
        bool fine = true;
        for (int i = 0; i < 26; i++) {
            if (new_map[i] == -1) {
                continue;
            }
            if (v[i].query(x, x + len - 1) != v[new_map[i]].query(y, y + len - 1)) {
                fine = false;
            }
        }
        if (!fine) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
}
