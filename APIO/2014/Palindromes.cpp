#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>
#include <map>
#include <random>
#include <cassert>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
 
int64_t binPow (int64_t x, int64_t y, int64_t MOD) {
    x %= MOD;
    int64_t res = x;
    int64_t ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x, int64_t MOD) {
    return binPow(x, MOD - 2, MOD);
}
vector<int64_t> powr = {1};
vector<int64_t> ipowr = {1};
struct Hasher {
    void resz (int mod, int base, string str) {
        int n = str.size();
        this->sz = n;
        this->MOD = mod, this->BASE = base;
        this->pref.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            pref[i] = (pref[i - 1] + (powr[n - i] * (str[i - 1] - 'a' + 1)) % MOD) % MOD;
            pref[i] %= MOD;
        }
    }
    int sz;
    int MOD;
    int BASE;
    vector<int64_t> pref;
    int64_t query (int l, int r) {
        if (l > sz || r > sz || l > r || l < 0 || r < 0) return -1;
        return (ipowr[sz - r - 1] * (pref[r + 1] - pref[l] + MOD) % MOD) % MOD;
    }
};
Hasher h1;
Hasher h2;
string s1;
bool isPalindrome (int l, int r) {
    if (l < 0 || r >= s1.length()) return false;
    return (h1.query(l, r) == h2.query((int)s1.length() - r - 1, (int)s1.length() - l - 1));
}
vector<int> suffix_array(string S) {
    int N = S.size();
    vector<int> sa(N), classes(N);
    for (int i = 0; i < N; i++) {
        sa[i] = N - 1 - i;
        classes[i] = S[i];
    }
    stable_sort(sa.begin(), sa.end(), [&S](int i, int j) {
        return S[i] < S[j];
    });
    for (int len = 1; len < N; len *= 2) {
        vector<int> c(classes);
        for (int i = 0; i < N; i++) {
            bool same = i && sa[i - 1] + len < N
                        && c[sa[i]] == c[sa[i - 1]]
                        && c[sa[i] + len / 2] == c[sa[i - 1] + len / 2];
            classes[sa[i]] = same ? classes[sa[i - 1]] : i;
        }
        vector<int> cnt(N), s(sa);
        for (int i = 0; i < N; i++)
            cnt[i] = i;
        for (int i = 0; i < N; i++) {
            int s1 = s[i] - len;
            if (s1 >= 0)
                sa[cnt[classes[s1]]++] = s1;
        }
    }
    return sa;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (powr.size() != 1e6 + 5) {
        powr.push_back(powr.back() * 31);
        powr.back() %= (int)1e9 + 9;
    }
    ipowr.resize(powr.size());
    ipowr[0] = 1; ipowr[1] = inv(powr[1], 1e9 + 9);
    for (int i = 2; i < powr.size(); i++) {
        ipowr[i] = (ipowr[i - 1] * ipowr[1]) % ((int)1e9 + 9);
    }
    cin >> s1;
    h1.resz((int)1e9 + 9, 31, s1);
    reverse(s1.begin(), s1.end());
    h2.resz((int)1e9 + 9, 31, s1);
    reverse(s1.begin(), s1.end());
    vector<pair<int,int>> vec;
    for (int i = 0;  i < s1.size(); i++) {
        int l = 0;
        int r = s1.length();
        while (l != r) {
            //cout << l << " " << r << '\n';
            int m = (l + r + 1)/2;
            if (isPalindrome(i - m, i + m)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        vec.emplace_back(i - l, i + l);
        //[...aa...]
        if (i == s1.length() || s1[i] != s1[i + 1]) {
            continue;
        }
        l = 0;
        r = s1.length();
        while (l != r) {
            int m = (l + r + 1)/2;
            if (isPalindrome(i - m, i + m + 1)) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        vec.emplace_back(i - l, i + l + 1);
        //cout << i << " " << l << '\n';
    }
    map<int64_t,pair<int,int>> myMap;
    for (auto& p: vec) {
        pair<int,int> q = p;
        while (q.first <= q.second) {
            if (myMap.count(h1.query(q.first, q.second))) {
                break;
            }
            myMap[h1.query(q.first, q.second)] = q;
            q.first++, q.second--;
        }
    }
    vector<int> v = suffix_array(s1);
    vector<int> id(v.size() + 1);
    for (int i = 0; i < v.size(); i++) {
        id[v[i]] = i;
    }
    int64_t ans = 0;
    for (auto& p: myMap) {
        int tot = h1.query(p.second.first, p.second.second);
        int l = 0;
        int r = id[p.second.first];
        while (l != r) {
            int m = (l + r)/2;
            if (h1.query(v[m], v[m] + p.second.second - p.second.first) == tot) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        int L = l;
        l = id[p.second.first];
        r = s1.length() - 1;
        while (l != r) {
            int m = (l + r + 1)/2;
            if (h1.query(v[m], v[m] + p.second.second - p.second.first) == tot) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (p.second.first - p.second.second == 2 && l - L + 1 == 10) {
            cout << p.second.first << " " << p.second.second << " " << l - L + 1 << '\n';
        }
        ans = max(ans, (int64_t)(p.second.second - p.second.first + 1) * (l - L + 1));
    }
    cout << ans;
}
